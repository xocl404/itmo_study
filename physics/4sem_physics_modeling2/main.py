import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import hsv_to_rgb

def wavelength_to_rgb(wavelength):
    if 380e-9 <= wavelength <= 750e-9:
        hue = (wavelength - 380e-9) / (750e-9 - 380e-9)  # нормализация
        return hsv_to_rgb([hue, 1.0, 1.0])
    else:
        return [0, 0, 0]  # вне видимого диапазона

def compute_thickness(X, Y, R):
    """
    Вычисление толщины воздушного зазора h(r) между линзой и пластиной.
    Формула из геометрии сферической линзы:
        h(r) = r² / (2R)
    где:
        r — расстояние до центра,
        R — радиус кривизны линзы.
    """
    r = np.sqrt(X ** 2 + Y ** 2)
    return r, r ** 2 / (2 * R)

def radial_profile(data, resolution, diameter):
    """
    Вычисление усреднённого радиального профиля интенсивности.
    Используется усреднение по кольцам равного радиуса.
    Возвращает:
        r_mm — массив расстояний от центра в мм
        radialprofile — средняя интенсивность по кольцам
    """
    center = resolution // 2
    y, x = np.indices((resolution, resolution))
    r = np.sqrt((x - center) ** 2 + (y - center) ** 2).astype(np.int32)
    tbin = np.bincount(r.ravel(), data.ravel())
    nr = np.bincount(r.ravel())
    radialprofile = tbin / np.maximum(nr, 1)

    pixel_size = diameter / resolution
    r_mm = np.arange(len(radialprofile)) * pixel_size * 1000
    return r_mm, radialprofile

def compute_intensity(h, wavelength):
    """
    Вычисление интерференционной интенсивности при нормальном падении.
    Формула (с учётом сдвига фаз π при отражении):
        I(r) = (1 + cos(4πh(r)/λ)) / 2
    """
    return (1 + np.cos(4 * np.pi * h / wavelength)) / 2


def compute_quasi_intensity(h, lambda_0, delta_lambda, n_samples):
    """
    Усреднение интенсивности по спектральному диапазону (для квазимонохроматического света).
    λ_i ∈ [λ₀ - Δλ/2, λ₀ + Δλ/2]
    I_quasi = (1/N) ∑ I(r, λ_i)
    """
    lambdas = np.linspace(lambda_0 - delta_lambda / 2, lambda_0 + delta_lambda / 2, n_samples)
    I_total = np.zeros_like(h)
    for lam in lambdas:
        I_total += compute_intensity(h, lam)
    return I_total / n_samples, lambdas


def compute_rgb_image(h, lambdas):
    rgb = np.zeros((*h.shape, 3))
    for lam in lambdas:
        I = compute_intensity(h, lam)
        color = wavelength_to_rgb(lam)
        for i in range(3):
            rgb[:, :, i] += I * color[i]
    rgb /= len(lambdas)
    return np.clip(rgb, 0, 1)

R = float(input("Радиус кривизны линзы R (в метрах) [по умолчанию 0.5]: ") or 0.5)
lambda_0 = float(input("Центральная длина волны λ₀ (в нм) [по умолчанию 550]: ") or 550) * 1e-9
delta_lambda = float(input("Ширина спектра Δλ (в нм) [по умолчанию 50]: ") or 50) * 1e-9
diameter_mm = 10  # размер изображения в мм
diameter = diameter_mm / 1000
resolution = 1000  # плотность сетки (1000x1000 точек)
n_samples = 50  # длины волн для квазимонохроматического случая

# Построение координатной сетки и расчёт толщины
x = np.linspace(-diameter / 2, diameter / 2, resolution)
y = np.linspace(-diameter / 2, diameter / 2, resolution)
X, Y = np.meshgrid(x, y)
r, h = compute_thickness(X, Y, R)

I_mono = compute_intensity(h, lambda_0)
plt.figure(figsize=(6, 6))
plt.imshow(I_mono, cmap='gray', extent=[-diameter_mm / 2, diameter_mm / 2, -diameter_mm / 2, diameter_mm / 2])
plt.title('Кольца Ньютона (монохроматический свет)')
plt.xlabel('x, мм')
plt.ylabel('y, мм')
plt.tight_layout()
plt.show()
r_vals, profile_mono = radial_profile(I_mono, resolution, diameter)
plt.figure(figsize=(8, 4))
plt.plot(r_vals, profile_mono)
plt.title('Профиль интенсивности (монохром.)')
plt.xlabel('r, мм')
plt.ylabel('Интенсивность')
plt.grid(True)
plt.tight_layout()
plt.show()

I_quasi, lambdas = compute_quasi_intensity(h, lambda_0, delta_lambda, n_samples)
rgb_image = compute_rgb_image(h, lambdas)
plt.figure(figsize=(6, 6))
plt.imshow(rgb_image, extent=[-diameter_mm / 2, diameter_mm / 2, -diameter_mm / 2, diameter_mm / 2])
plt.title('Кольца Ньютона (квазимонохроматический свет)')
plt.xlabel('x, мм')
plt.ylabel('y, мм')
plt.tight_layout()
plt.show()
avg_intensity = rgb_image.mean(axis=2)
r_vals, profile_quasi = radial_profile(avg_intensity, resolution, diameter)
plt.figure(figsize=(8, 4))
plt.plot(r_vals, profile_quasi)
plt.title('Профиль интенсивности (квазимонохром.)')
plt.xlabel('r, мм')
plt.ylabel('Интенсивность (усреднённая)')
plt.grid(True)
plt.tight_layout()
plt.show()
