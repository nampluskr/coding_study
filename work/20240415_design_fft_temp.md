# FFT

## 현재 사용예

### 이미지 불러오기

```python
raw1 = skimage.data.camera()            # ndarray
raw2 = Image().path(r"lena.jpg").load() # ndarray

# Image()
# input: ndarry -> output: ndarry
img1 = Image(raw1).gray().resize(100, 100).minmax(0, 1).load()
img2 = Image(raw2).gray().resize(100, 100).minmax(0, 1).load()
```

### 이미지 보기

```python
Viwer(img1).show()
Viwer(img2).show_fft()
```

### FFT 처리

```python
ft = FFT(img1)
ft_amp = ft.amp
ft_ang = ft.ang

img1_rev = IFFT(ft_amp, ft_ang).real()  # .abs()
```

## 최종 상용예

```python
raw1 = plt.imread("lena.jpg")
img1 = Image(raw1).gray().resiz(w, h).minmax(a, b).load() # ndarry

Viewer(img1).figsize(6, 4).cmap("jet").show()
```

```python
ft = FFT(img1)  # fft, amp, ang -> log10(abs(amp))
amp = ft.amp    # ndarry
ang = ft.ang    # ndarry

ft_img = FFT(img1)      ## FFT Object
amp = ft_img.fft().amp().abs().log1p()
ang = ft_img.fft().ang()

ft_img = FFTShift(img1)
amp = ft_img.amp().abs()
```

```python
class BaseFFT:
    def __init__(self, data: ndarry):
        self.data = data
        self.fft = None

    def apply_fft(self):
        pass

    def amplitude(self):
        return None if self.fft is None else np.abs(self.fft)

    def phase(self):
        return None if self.fft is None else np.angle(self.fft)

class FFT(BaseFFT):
    def apply_fft(self):
        self.fft = fft2d(self.data)

class FFTShift(BaseFFT):
    def apply_fft(self):
        self.fft = fftshift2d(fft2d(self.data))
```

```python
class BaseFFT:
    def __init__(self, data: ndarry):
        self.data = data
        self.fft = self.transform()
        self.amp = self.amplitude()
        self.ang = self.phase()

    def transform(self):
        pass

    def amplitude(self):
        return np.abs(self.fft)

    def phase(self):
        return np.angle(self.fft)

class FFT(BaseFFT):
    def transform(self):
        return fft2d(self.data)

class FFTShift(BaseFFT):
    def transform(self):
        return fftshift2d(fft2d(self.data))
```

