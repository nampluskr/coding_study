### [config.py] fft 파이썬 코드

```python
import os
from glob import glob

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

from skimage.color import xyz2rgb, rgb2xyz

class Data:
    def __init__(self, target_dir, filename, csv_dir=None):
        self.target_dir = target_dir
        self.filename = filename
        self.filepath = os.path.join(self.target_dir, self.filename + ".npz")

        param = filename.split()
        self.freq = param[1]
        self.dimming = param[2]
        self.signal = param[3]

        if csv_dir is not None:
            self.csv_dir = csv_dir

    def load_csv(self):
        if self.csv_dir is not None:
            self.x_csv_path = os.path.join(self.csv_dir, self.filename + "_X.csv")
            self.y_csv_path = os.path.join(self.csv_dir, self.filename + "_Y.csv")
            self.z_csv_path = os.path.join(self.csv_dir, self.filename + "_Z.csv")

            self.x = pd.read_csv(self.x_csv_path).to_numpy()
            self.y = pd.read_csv(self.x_csv_path).to_numpy()
            self.z = pd.read_csv(self.x_csv_path).to_numpy()
            
            self.height = self.x.shape[0]
            self.width = self.x.shape[1]

            print(f">> X: {self.x.shape}, Y: {self.y.shape} Z: {self.z.shape}: {self.filename}")

    def save(self):
        np.savez_compressed(self.filepath, x=self.x, y=self.y, z=self.z)

    def load(self):
        data = np.load(self.filepath)
        self.x = data['x']
        self.y = data['y']
        self.z = data['z']
        
        self.height = self.x.shape[0]
        self.width = self.x.shape[1]
        self.xyz = self.get_xyz()
        self.rgb = xyz2rgb(self.xyz)
      
    def get_xyz(self):
        xyz = np.empty(shape=(self.height, self.width, 3), dtype=float)
        xyz[:, :, 0] = self.x
        xyz[:, :, 1] = self.y
        xyz[:, :, 2] = self.z
        return xyz
    
    def get_rgb(self):
        xyz = self.get_xyz()
        rgb = xyz2rgb(xyz)
        return rgb

    def show(self):
        # cmap = plt.cm.Greys
        print(f">> {self.filename}")
        fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=(10, 3))
        ax1.imshow(self.y, cmap=plt.cm.Greys_r); ax1.set_title("Y")
        ax2.imshow(self.xyz); ax2.set_title("XYZ")
        ax3.imshow(self.rgb); ax3.set_title("RGB")
        fig.tight_layout()
        plt.show()


def get_filenames(data_dir, ext="csv"):
    if ext == "csv":
        file_paths = glob(os.path.join(data_dir, "*_?.csv"))
        file_names = list(set([os.path.basename(name)[:-6] for name in file_paths]))
    elif ext == "npz":
        file_paths = glob(os.path.join(data_dir, "*.npz"))
        file_names = [os.path.basename(name)[:-4] for name in file_paths]
        
    file_names.sort(reverse=True)
    return file_names


if __name__ == "__main__":

    pass
```

### [3d contour plot]

```python
raw = skimage.io.imread("lena.jpg")
img = skimage.color.rgb2gray(raw)
X = np.linspace(0, img.shape[1] - 1, img.shape[1])
Y = np.linspace(0, img.shape[0] - 1, img.shape[0])
X, Y = np.meshgrid(X, Y)

ft = fftshift(fft2(img))
ft_amp = np.log1p(np.abs(ft))
ft_ang = np.angle(ft)
img_inv = np.abs(ifft2(np.exp(ft_amp + 1j*ft_ang)))


fig, (ax1, ax2, ax3, ax4) = plt.subplots(1, 4, figsize=(12, 3))
ax1.imshow(img, cmap='jet')
ax2.imshow(skimage.filters.gaussian(ft_amp, sigma=2), cmap='jet')
ax3.imshow(skimage.filters.gaussian(ft_ang, sigma=2), cmap='jet')
ax4.imshow(img_inv - img, cmap='jet')
fig.tight_layout()
plt.show()


fig, (ax1, ax2, ax3, ax4) = plt.subplots(1, 4, figsize=(12, 4), subplot_kw={"projection": "3d"})
ax1.plot_surface(X, Y, img, cmap='jet')
ax2.plot_surface(X, Y, skimage.filters.gaussian(ft_amp, sigma=2), cmap='jet')
ax3.plot_surface(X, Y, skimage.filters.gaussian(ft_ang, sigma=2), cmap='jet')
ax4.plot_surface(X, Y, img_inv - img, cmap='jet')
fig.tight_layout()
plt.show()
```
