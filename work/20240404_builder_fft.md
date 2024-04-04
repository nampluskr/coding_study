### builder

```python
from __future__ import annotations
import functools

import numpy as np
import matplotlib.pyplot as plt
from scipy.fft import fft2 as fft2d, fftshift as fftshift2d
from scipy.fft import ifft2 as ifft2d, ifftshift as ifftshift2d

import skimage


class StatData:
    def __init__(self, data: np.ndarray=None):
        if isinstance(data, ImageData):
            self.data = data.data
        else:
            self.data = data
        
        self.avg = self.data.mean()
        self.std = self.data.std()
        self.min = self.data.min()
        self.max = self.data.max()

    def info(self):
        print(f">> min={self.min:.2f}, max={self._max:.2f}", end=", ")
        print(f"avg={self.avg:.2f}, std={self._std:.2f}")


## === Product Class in Builder Pattern ===
## image ndarray data
class ImageData:
    def __init__(self, data=None):
        self.data = data

    def info(self):
        print(f">> shape={self.data.shape}, dtype={self.data.dtype}", end=", ")
        print(f"min={self.data.min():.2f}, max={self.data.max():.2f}")

    # setter
    def gray(self) -> ImageData:
        assert self.data is not None
        if self.data.ndim > 2:
            if self.data.shape[-1] > 3:
                self.data = skimage.color.rgba2rgb(self.data)
            self.data = skimage.color.rgb2gray(self.data)
        return self

    # setter
    def rescale(self, min:int, max:int) -> ImageData:
        assert self.data is not None
        data_min_max = self.data.min(), self.data.max()
        self.data = np.interp(self.data, data_min_max, (min, max))
        return self

    # setter
    def resize(self, height: int, width: int) -> ImageData:
        assert self.data is not None
        self.data = skimage.transform.resize(self.data, (height, width))
        return self


## === Builder Class in Builder Pattern ===
# image loader
class ImageLoader:
    def __init__(self, data: np.ndarray=None):
        self.img = ImageData(data)

    def from_path(self, path: str) -> ImageLoader:
        self.img = ImageData(skimage.io.imread(path))
        return self

    def gray(self) -> ImageLoader:
        self.img.gray()
        return self

    def resize(self, height: int, width: int) -> ImageLoader:
        self.img.resize(height, width)
        return self

    def rescale(self, min: int, max:int) -> ImageLoader:
        self.img.rescale(min, max)
        return self

    def load(self) -> ImageData:
        return self.img


## === Application for ImageData object
class FFT:
    def __init__(self, data):
        if isinstance(data, ImageData):
            self.data = data.data
        else:
            self.data = data
            
        self.fft = fftshift2d(fft2d(self.data))
        self.amp = np.log1p(np.abs(self.fft))
        self.ang = np.angle(self.fft)


def ifft_real(amp: np.ndarray, ang: np.ndarray=None) -> np.ndarray:
    if ang is None:
        # amp is complex array
        return ifft2d(ifftshift2d(amp)).real
    else:
        return ifft2d(ifftshift2d(np.exp(amp + 1j*ang))).real


def ifft_abs(amp: np.ndarray, ang: np.ndarray=None) -> np.ndarray:
    if ang is None:
        # amp is complex array
        return np.abs(ifft2d(ifftshift2d(amp)))
    else:
        return np.abs(ifft2d(ifftshift2d(np.exp(amp + 1j*ang))))
    

## === Application for ImageData object
class ImageViwer:
    def __init__(self, data):
        if isinstance(data, ImageData):
            self.data = data.data
        else:
            self.data = data
        
        if self.data is not None:
            M, N = self.data.shape
            self.ext_amp = (-M//2, M//2, -N//2, N//2)
            self.ext_ang = (-np.pi/2, np.pi/2, -np.pi/2, np.pi/2)
            self.cm = "gray"
            self.is_axis_off = False
            self.figsize = (6, 4)
            self.is_amp = self.is_ang = False
        else:
            self.data = None

    def info(self) -> ImageViwer:
        ImageData(self.data).info()
        return self

    def axis_off(self) -> ImageViwer:
        self.is_axis_off = True
        return self

    def cmap(self, cm: str) -> ImageViwer:
        self.cm = cm
        return self

    def resize(self, width: int, height: int) -> ImageViwer:
        self.figsize = width, height
        return self

    def amp(self) -> ImageViwer:
        self.is_amp = True
        self.is_ang = False
        return self

    def ang(self) -> ImageViwer:
        self.is_amp = False
        self.is_ang = True
        return self

    def show(self) -> None:
        assert self.data is not None

        fig, ax = plt.subplots(figsize=self.figsize)
        if self.is_amp:
            ax.imshow(self.data, cmap=self.cm, extent=self.ext_amp)
            ax.set_title("Amplitude", fontsize=12)
            M, N = self.data.shape
            ax.set_xticks([-N//2, -N//4, 0, N//4, N//2])
            ax.set_yticks([-M//2, -M//4, 0, M//4, M//2])
        elif self.is_ang:
            ax.imshow(self.data, cmap=self.cm, extent=self.ext_ang)
            ax.set_title("Phase", fontsize=12)
            ax.set_xticks([-np.pi/2, 0, np.pi/2])
            ax.set_yticks([-np.pi/2, 0, np.pi/2])
            ax.set_xticklabels(["-$\pi/2$", 0, "$\pi/2$"])
            ax.set_yticklabels(["-$\pi/2$", 0, "$\pi/2$"])
        else:
            ax.imshow(self.data, cmap=self.cm)

        if self.is_axis_off:
            ax.set_axis_off()

        fig.tight_layout()
        plt.show()

    def show_fft(self) -> None:
        assert self.data is not None
        fft = FFT(self.data)

        fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=self.figsize)
        ax1.imshow(self.data, cmap=self.cm)
        ax2.imshow(fft.amp, cmap=self.cm, extent=self.ext_amp)
        ax3.imshow(fft.ang, cmap=self.cm, extent=self.ext_ang)

        if self.is_axis_off:
            ax1.set_axis_off()
            ax2.set_axis_off()
            ax3.set_axis_off()
        else:
            ax2.set_title("Amplitude", fontsize=12)
            ax3.set_title("Phase", fontsize=12)

            M, N = self.data.shape
            ax2.set_xticks([-N//2, -N//4, 0, N//4, N//2])
            ax2.set_yticks([-M//2, -M//4, 0, M//4, M//2])

            ax3.set_xticks([-np.pi/2, 0, np.pi/2])
            ax3.set_yticks([-np.pi/2, 0, np.pi/2])
            ax3.set_xticklabels(["-$\pi/2$", 0, "$\pi/2$"])
            ax3.set_yticklabels(["-$\pi/2$", 0, "$\pi/2$"])

        fig.tight_layout()
        plt.show()


def get_mask(rows, cols, dr, dc, vmin=0, vmax=1):
    cr, cc = rows // 2, cols // 2
    mask = np.ones((rows, cols), np.uint8) * vmin
    mask[-cr-dr:cr+dr, -cc-dc:cc+dc] = vmax
    return mask


if __name__ == "__main__":

    path_img1 = r"D:\Non_Documents\work_2024\images\lena.jpg"

    img1 = ImageLoader().from_path(path_img1).gray().load()
    img2 = ImageLoader(skimage.data.camera()).gray().rescale(0, 1).load()

    fft1 = FFT(img1.data)
    fft2 = FFT(img2.data)

    if 0:
        ImageViwer(img1).resize(3, 3).axis_off().info().show()
        ImageViwer(img2).resize(3, 3).axis_off().info().show()

    if 0:
        ImageViwer(fft1.amp).amp().info().show()
        ImageViwer(fft1.ang).ang().info().show()

    if 0:
        ImageViwer(img1.data).resize(9, 3).axis_off().info().show_fft()
        ImageViwer(img2.data).resize(9, 3).info().show_fft()

    if 1:
        img1_inv = ImageLoader(ifft_abs(fft1.amp, fft1.ang)).load()
        ImageViwer(img1_inv.data).resize(9, 3).info().show_fft()
```
