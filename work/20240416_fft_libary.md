### [filter.py]

```python
import numpy as np
from numpy import ndarray
from scipy.ndimage import uniform_filter, gaussian_filter

class Filter:
    def __init__(self, data: ndarray):
        self.data = data
        self.rows = data.shape[0]
        self.cols = data.shape[1]
    
    def gaussian(self, sigma=1) -> ndarray:
        return gaussian_filter(self.data, sigma=sigma)
    
    def uniform(self, size=1) -> ndarray:
        return uniform_filter(self.data, size=size, mode="nearest")

    def mask(self, dr, dc, base, value) -> ndarray:
        cr, cc = self.rows//2, self.cols//2
        mask = np.ones_like(self.data, dtype=np.uint8)*base
        mask[-cr-dr:cr+dr, -cc-dc:cc+dc] = value
        return mask
```


### [image.py]

```python
from __future__ import annotations
import numpy as np
from numpy import ndarray
import skimage


## ==================================================================
class Image:
    def __init__(self, data: ndarray=None):
        self.data = data

    def path(self, path) -> Image:
        self.data = skimage.io.imread(path)
        return self

    def gray(self) -> Image:
        assert self.data is not None
        if self.data.ndim > 2:
            if self.data.shape[-1] > 3:
                self.data = skimage.color.rgba2rgb(self.data)
            self.data = skimage.color.rgb2gray(self.data)
        return self

    def resize(self, width, height) -> Image:
        assert self.data is not None
        self.data = skimage.transform.resize(self.data, (width, height))
        return self

    def minmax(self, min, max) -> Image:
        assert self.data is not None
        data_min_max = self.data.min(), self.data.max()
        self.data = np.interp(self.data, data_min_max, (min, max))
        return self

    def info(self):
        print(f">> shape={self.data.shape}, dtype={self.data.dtype}", end=", ")
        print(f"min={self.data.min():.2f}, max={self.data.max():.2f}")
        return self

    def apply(self, data: ndarray):
        if self.is_gray:
            data = Image(data).gray().data
        if self.height != data.shape[0] or self.width != data.data[1]:
            data = Image(data).resize(self.height, self.width).data
        if self.min != data.min() or self.max() != data.max():
            data = Image(data).minmax(min, max)
        return data
```

### [fft.py]

```python
from __future__ import annotations
import numpy as np
import matplotlib.pyplot as plt
from numpy import ndarray
from scipy.fft import fft2, ifft2, fftshift, ifftshift


## ==================================================================
class BaseFFT:
    def __init__(self, data: ndarray):
        self.data = data
        self.fft = self.transform()
        self.amp = self.amplitude()
        self.ang = self.phase()

        self.size = (9, 3)
        self.cm = "gray"
        self.is_axis_off = False
        self.extent = None
        self.xticks = None
        self.yticks = None
        self.tickslabels = None

    def cmap(self, cm: str) -> BaseFFT:
        self.cm = cm
        return self

    def figsize(self, width, height) -> BaseFFT:
        self.size = width, height
        return self

    def axis_off(self) -> BaseFFT:
        self.is_axis_off = True
        return self

    def transform(self) -> ndarray:
        return None

    def amplitude(self) -> ndarray:
        return np.abs(self.fft)

    def phase(self) -> ndarray:
        return np.angle(self.fft)

    def show(self) -> None:
        fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=self.size)
        ax1.imshow(self.data, cmap=self.cm)
        ax2.imshow(np.log1p(self.amp), cmap=self.cm, extent=self.extent)
        ax3.imshow(self.ang, cmap=self.cm, extent=self.extent)

        ax2.set_title("Amplitude", fontsize=12)
        ax3.set_title("Phase", fontsize=12)

        for ax in (ax2, ax3):
            ax.set_xticks(self.xticks)
            ax.set_yticks(self.yticks)

        ax3.set_xticklabels(self.tickslabels)
        ax3.set_yticklabels(self.tickslabels)

        if self.is_axis_off:
            for ax in (ax1, ax2, ax3):
                ax.set_axis_off()

        fig.tight_layout()
        plt.show()


class FFT(BaseFFT):
    def transform(self) -> ndarray:
        return fft2(self.data)

    def show(self) -> None:
        M, N = self.data.shape[:2]
        self.extent = (0, N, 0, M)
        self.xticks = (0, N//4, N//2, 3*N//4, N)
        self.yticks = (0, M//4, M//2, 3*M//4, M)
        self.tickslabels = (0, "$\pi/2$", "$\pi$", "$3\pi/2$", "$2\pi$")
        super().show()


class FFTShift(BaseFFT):
    def transform(self) -> ndarray:
        return fftshift(fft2(self.data))

    def show(self) -> None:
        M, N = self.data.shape[:2]
        self.extent = (-N//2, N//2, -M//2, M//2)
        self.xticks = (-N//2, -N//4, 0, N//4, N//2)
        self.yticks = (-M//2, -M//4, 0, M//4, M//2)
        self.tickslabels = ("-$\pi$", "-$\pi/2$", "0", "$\pi/2$", "$\pi$")
        super().show()


## ==================================================================
class BaseInvFFT:
    def __init__(self, amp: ndarray, ang: ndarray=None):
        if ang is None:
            self.fft = amp
        else:
            self.fft = amp * np.exp(1j * ang)
        self.ifft = self.transform()

    def transform(self) -> ndarray:
        return None

    def abs(self):
        return np.abs(self.ifft)

    def real(self):
        return np.real(self.ifft)


class InvFFT(BaseInvFFT):
    def transform(self) -> ndarray:
        return ifft2(self.fft)


class InvFFTShift(BaseInvFFT):
    def transform(self) -> ndarray:
        return ifft2(ifftshift(self.fft))
```

### [viewer.py]

```python
from __future__ import annotations
import numpy as np
import matplotlib.pyplot as plt
from numpy import ndarray


## ==================================================================
class Viewer:
    def __init__(self, data: ndarray=None):
        self.data = data
        self.cm = "gray"
        self.size = (6, 4)
        self.is_axis_off = False

    def cmap(self, cm: str) -> Viewer:
        self.cm = cm
        return self

    def figsize(self, width, height) -> Viewer:
        self.size = width, height
        return self

    def axis_off(self) -> Viewer:
        self.is_axis_off = True
        return self

    def show(self, img: ndarray=None) -> None:
        data = self.data if img is None else img
        fig, ax = plt.subplots(figsize=self.size)
        ax.imshow(data, cmap=self.cm)
        if self.is_axis_off:
            ax.set_axis_off()
        fig.tight_layout()
        plt.show()
        
    def show3d(self, img: ndarray=None) -> None:
        data = self.data if img is None else img
        Y = np.linspace(0, data.shape[0] - 1, data.shape[0])
        X = np.linspace(0, data.shape[1] - 1, data.shape[1])
        Y, X = np.meshgrid(Y, X)

        fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
        ax.plot_surface(Y, X, data, cmap="inferno")
        ax.set_xlabel("height")
        ax.set_ylabel("width")
        ax.view_init(elev=45, azim=-20)
        if self.is_axis_off:
            ax.set_axis_off()
        fig.tight_layout()
        plt.show()

## ==================================================================
class FFTViewer(Viewer):
    def __init__(self, data: ndarray=None):
        super().__init__(data)
        self.is_amp = False
        self.is_ang = False

    def amp(self) -> Viewer:
        self.is_amp = True
        self.is_ang = False
        self.is_axis_off = False
        return self

    def ang(self) -> Viewer:
        self.is_amp = False
        self.is_ang = True
        self.is_axis_off = False
        return self

    def show(self, img: ndarray=None) -> None:
        data = self.data if img is None else img
        fig, ax = plt.subplots(figsize=self.size)

        if self.is_amp or self.is_ang:
            M, N = data.shape[:2]
            ax.imshow(data, cmap=self.cm, extent=(-N//2, N//2, -M//2, M//2))
            ax.set_xticks((-N//2, -N//4, 0, N//4, N//2))
            ax.set_yticks((-M//2, -M//4, 0, M//4, M//2))
        else:
            ax.imshow(data, cmap=self.cm)

        if self.is_amp:
            ax.set_title("Amplitude", fontsize=12)

        if self.is_ang:
            ax.set_title("Phase", fontsize=12)
            ax.set_xticklabels(["-$\pi$", "-$\pi/2$", 0, "$\pi/2$", "$\pi$"])
            ax.set_yticklabels(["-$\pi$", "-$\pi/2$", 0, "$\pi/2$", "$\pi$"])

        if self.is_axis_off:
            ax.set_axis_off()
            ax.set_title("")

        fig.tight_layout()
        plt.show()
```
