### `fft.py`

```python
from __future__ import annotations
import numpy as np

from scipy.fft import fft2 as fft2d, fftshift as fftshift2d
from scipy.fft import ifft2 as ifft2d, ifftshift as ifftshift2d
from scipy.fft import dct, idct
from scipy.ndimage import uniform_filter, gaussian_filter

from image import Data


class FFT:
    def __init__(self, data):
        if isinstance(data, Data):
            self.data = data.data
        else:
            self.data = data

        self.fft = fft2d(self.data)
        self.amp = np.abs(self.fft)
        self.amp_log = np.log1p(self.amp)
        self.ang = np.angle(self.fft)
        
    def cepstrum(self):
        fft_log = FFT(self.amp_log)
        return IFFT(fft_log.fft).real()

    def salency_map(self, sigma=2):
        amp_avg = uniform_filter(self.amp, size=3, mode="nearest")
        amp_res = self.amp - amp_avg
        sm = np.abs(IFFT(amp_res, self.ang).pow(2))
        return gaussian_filter(sm, sigma=sigma)

    def phase_correlation(self, data):
        if isinstance(data, Data):
            fft2 = FFT(data.data).fft
        else:
            fft2 = FFT(data).fft

        R = self.fft * fft2.conj()
        return IFFT(R / np.abs(R)).abs()

    def phase_discrepancy(self, data):
        if isinstance(data, Data):
            fft2 = FFT(data.data)
        else:
            fft2 = FFT(data)

        amp1, ang1 = self.amp, self.ang
        amp2, ang2 = fft2.amp, fft2.ang

        ifft1 = IFFT(amp2 - amp1, ang1).abs()
        ifft2 = IFFT(amp2 - amp1, ang2).abs()
        res = ifft1 * ifft2
        return np.interp(res, (res.min(), res.max()), (0, 255))


class IFFT:
    def __init__(self, amp, ang=None):
        if ang is None: # amp: complex
            self.ifft = ifft2d(amp)
        else:           # amp = np.expm1(amp_log)
            self.ifft = ifft2d(amp*np.exp(1j*ang))

    def abs(self):
        return np.abs(self.ifft)

    def real(self):
        return self.ifft.real

    def pow(self, n):
        return self.ifft ** n


class FFTShift:
    def __init__(self, data):
        if isinstance(data, Data):
            self.data = data.data
        else:
            self.data = data

        self.fft = fftshift2d(fft2d(self.data))
        self.amp = np.abs(self.fft)
        self.amp_log = np.log1p(np.abs(self.fft))
        self.ang = np.angle(self.fft)
        
    def cepstrum(self):
        fft_log = FFTShift(self.amp_log)
        return IFFTShift(fft_log.fft).real()


class IFFTShift:
    def __init__(self, amp, ang=None):
        if ang is None: # amp is complex
            self.ifft = ifft2d(ifftshift2d(amp))
        else:           # amp = np.expm1(amp_log)
            self.ifft = ifft2d(ifftshift2d(amp*np.exp(1j*ang)))

    def abs(self):
        return np.abs(self.ifft)

    def real(self):
        return self.ifft.real

    def pow(self, n):
        return self.ifft ** n


class DCT:
    def __init__(self, data):
        if isinstance(data, Data):
            self.data = data.data
        else:
            self.data = data

        self.dct = dct(dct(self.data.T, type=2, norm='ortho').T, type=2, norm='ortho')
        self.amp = np.abs(self.dct)
        self.amp_log = np.log1p(np.abs(self.dct))

    def mura(self, threshold=100):
        dct_th = self.dct.copy()
        dct_th[self.amp < threshold] = 0
        data_inv = IDCT(dct_th).abs()
        return np.abs(self.data - data_inv)


class IDCT:
    def __init__(self, data: np.ndarray):
        # if amp_log => np.expm1(amp_log).T
        self.idct = idct(idct(data.T, type=2, norm='ortho').T, type=2, norm='ortho')

    def abs(self):
        return np.abs(self.idct)
```

### `image.py`

```python
from __future__ import annotations
import functools

import numpy as np
import matplotlib.pyplot as plt
import skimage


class Data:
    def __init__(self, data=None):
        if isinstance(data, str):
            self.data = skimage.io.imread(data)
        else:
            self.data = data

    def info(self):
        print(f">> shape={self.data.shape}, dtype={self.data.dtype}", end=", ")
        print(f"min={self.data.min():.2f}, max={self.data.max():.2f}")
        return self


class Image(Data):
    def __init__(self, data=None):
        self.data = Data(data).data

    def gray(self) -> Image:
        assert self.data is not None
        if self.data.ndim > 2:
            if self.data.shape[-1] > 3:
                self.data = skimage.color.rgba2rgb(self.data)
            self.data = skimage.color.rgb2gray(self.data)
        return self

    def rescale(self, min:int, max:int) -> Image:
        assert self.data is not None
        data_min_max = self.data.min(), self.data.max()
        self.data = np.interp(self.data, data_min_max, (min, max))
        return self

    def resize(self, width: int, height: int) -> Image:
        assert self.data is not None
        self.data = skimage.transform.resize(self.data, (height, width))
        return self


class Stat:
    def __init__(self, data=None):
        if isinstance(data, Data):
            self.data = data.data
        else:
            self.data = data

        self.avg = self.data.mean()
        self.std = self.data.std()
        self.min = self.data.min()
        self.max = self.data.max()

    def info(self):
        print(f">> min={self.min:.2f}, max={self.max:.2f}", end=", ")
        print(f"avg={self.avg:.2f}, std={self.std:.2f}")


if __name__ == "__main__":

    img1 = Image(r"D:\Non_Documents\work_2024\images\lena.jpg").gray()
    img2 = Image(skimage.data.camera()).gray().rescale(0, 1)

    img1.info()
    img2.info()

    Stat(img1).info()
    Stat(img2).info()
```

### `viewer.py`

```python
from __future__ import annotations
import numpy as np
import matplotlib.pyplot as plt

from image import Data, Image
from fft import FFT, FFTShift


class Graph:
    def axis_off(self) -> Graph:
        self.is_axis_off = True
        return self

    def cmap(self, cm: str) -> Graph:
        self.cm = cm
        return self

    def resize(self, width: int, height: int) -> Graph:
        self.figsize = width, height
        return self

class Viewer(Graph):
    def __init__(self, data):
        if isinstance(data, Data):
            self.data = data.data
        else:
            self.data = data

        if self.data is not None:
            M, N = self.data.shape
            self.extent = (-N//2, N//2, -M//2, M//2)
            self.cm = "gray"
            self.is_axis_off = False
            self.figsize = (6, 4)
            self.is_amp = self.is_ang = False
        else:
            self.data = None

    def info(self) -> Viewer:
        Data(self.data).info()
        return self

    def amp(self) -> Viewer:
        self.is_amp = True
        self.is_ang = False
        return self

    def ang(self) -> Viewer:
        self.is_amp = False
        self.is_ang = True
        return self

    def show(self) -> None:
        assert self.data is not None

        fig, ax = plt.subplots(figsize=self.figsize)
        if self.is_amp:
            ax.imshow(self.data, cmap=self.cm, extent=self.extent)
            ax.set_title("Amplitude", fontsize=12)
            M, N = self.data.shape
            ax.set_xticks([-N//2, -N//4, 0, N//4, N//2])
            ax.set_yticks([-M//2, -M//4, 0, M//4, M//2])
        elif self.is_ang:
            ax.imshow(self.data, cmap=self.cm, extent=self.extent)
            ax.set_title("Phase", fontsize=12)
            M, N = self.data.shape
            ax.set_xticks([-N//2, -N//4, 0, N//4, N//2])
            ax.set_yticks([-M//2, -M//4, 0, M//4, M//2])
            ax.set_xticklabels(["-$\pi$", "-$\pi/2$", 0, "$\pi/2$", "$\pi$"])
            ax.set_yticklabels(["-$\pi$", "-$\pi/2$", 0, "$\pi/2$", "$\pi$"])
        else:
            ax.imshow(self.data, cmap=self.cm)

        if self.is_axis_off:
            ax.set_axis_off()

        fig.tight_layout()
        plt.show()

    def show_fft(self) -> None:
        assert self.data is not None
        fft = FFTShift(self.data)

        fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=self.figsize)
        ax1.imshow(self.data, cmap=self.cm)
        ax2.imshow(np.log1p(fft.amp), cmap=self.cm, extent=self.extent)
        ax3.imshow(fft.ang, cmap=self.cm, extent=self.extent)

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

            ax3.set_xticks([-N//2, -N//4, 0, N//4, N//2])
            ax3.set_yticks([-M//2, -M//4, 0, M//4, M//2])
            ax3.set_xticklabels(["-$\pi$", "-$\pi/2$", 0, "$\pi/2$", "$\pi$"])
            ax3.set_yticklabels(["-$\pi$", "-$\pi/2$", 0, "$\pi/2$", "$\pi$"])

        fig.tight_layout()
        plt.show()

if __name__ == "__main__":

    import skimage

    img1 = Image(r"D:\Non_Documents\work_2024\images\lena.jpg").gray()
    img2 = Image(skimage.data.camera()).gray().rescale(0, 1)

    # Viewer(img1).axis_off().info().show()

    fft1 = FFT(img1)
    Viewer(fft1.amp).amp().cmap("jet").show()
    Viewer(fft1.ang).ang().cmap("jet").show()
    Viewer(img1).resize(12, 4).show_fft()
```

### `utyls.py`

```python
import numpy as np

def get_mask(rows, cols, dr, dc, vmin=0, vmax=1):
    cr, cc = rows // 2, cols // 2
    mask = np.ones((rows, cols), np.uint8) * vmin
    mask[-cr-dr:cr+dr, -cc-dc:cc+dc] = vmax
    return mask


if __name__ == "__main__":

    pass
```
