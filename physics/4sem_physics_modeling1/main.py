import numpy as np
import matplotlib.pyplot as plt
from scipy.constants import e, m_e, mu_0

class ElectronOrbitModel:
    def __init__(self, radius_anode, radius_cathode, turns_per_meter, voltage_min, voltage_max):
        # Задаём геометрию и параметры соленоида
        self.Ra = radius_anode          # Радиус анода (м)
        self.Rk = radius_cathode        # Радиус катода (м)
        self.n = turns_per_meter        # Число витков на единицу длины (витков/м)
        self.U_min = voltage_min        # Минимальное напряжение (В)
        self.U_max = voltage_max        # Максимальное напряжение (В)

    def critical_current(self, U):
        """
        Вычисляем ток соленоида, при котором электрон движется по окружности радиуса (Ra - Rk)/2.
        Используем:
        - Закон сохранения энергии: (1/2)mv² = eU
        - Центростремительное ускорение: mv²/r = evB
        => B = sqrt(2 * m_e * e * U) / (e * r)
        => Ic = B / (μ₀ * n)
        """
        r = (self.Ra - self.Rk) / 2
        B_required = np.sqrt(2 * m_e * U / e) / r
        return B_required / (mu_0 * self.n)

    def compute_trajectory(self, points=1000):
        """
        Строим координаты траектории электрона — окружность радиуса r с центром на расстоянии Rk + r
        от центра координат.
        """
        r = (self.Ra - self.Rk) / 2
        center = self.Rk + r
        theta = np.linspace(0, 2 * np.pi, points)
        x = center * np.cos(theta)
        y = center * np.sin(theta)
        return x, y

    def plot_current_vs_voltage(self, steps=200):
        """
        Строим график зависимости тока Ic от напряжения U.
        """
        voltages = np.linspace(self.U_min, self.U_max, steps)
        currents = np.array([self.critical_current(U) for U in voltages])

        plt.figure(figsize=(10, 6))
        plt.plot(voltages, currents, color='navy', label='Ic(U)', linewidth=2)
        plt.fill_between(voltages, currents, currents.max(), color='lightgreen', alpha=0.3,
                         label='Область устойчивого движения')
        plt.xlabel('Напряжение (В)')
        plt.ylabel('Критический ток Ic (А)')
        plt.title('График зависимости тока соленоида от напряжения')
        plt.grid(True)
        plt.legend()
        plt.tight_layout()
        plt.show()

        print(f"Диапазон напряжения: от {self.U_min} В до {self.U_max} В")
        print(f"Параметры соленоида: n = {self.n} витков/м, Ra = {self.Ra} м, Rk = {self.Rk} м")

    def plot_orbit(self, U):
        """
        Строим траекторию электрона при заданном напряжении U.
        """
        Ic = self.critical_current(U)
        x, y = self.compute_trajectory()

        fig, ax = plt.subplots(figsize=(7, 7))
        ax.plot(x, y, 'darkred', linewidth=1.8, label='Траектория электрона')

        theta = np.linspace(0, 2 * np.pi, 500)
        ax.plot(self.Rk * np.cos(theta), self.Rk * np.sin(theta), 'b--', label='Катод')
        ax.plot(self.Ra * np.cos(theta), self.Ra * np.sin(theta), 'g--', label='Анод')

        ax.set_aspect('equal')
        ax.set_xlim(-self.Ra * 1.2, self.Ra * 1.2)
        ax.set_ylim(-self.Ra * 1.2, self.Ra * 1.2)
        ax.set_xlabel('x (м)')
        ax.set_ylabel('y (м)')
        ax.set_title(f'Траектория электрона при U = {U} В\nIc = {Ic:.3f} А')
        ax.grid(True)
        ax.legend()
        plt.tight_layout()
        plt.show()

        print(f"Напряжение: U = {U} В")
        print(f"Рассчитанный ток соленоида: Ic = {Ic:.4f} А")

print("Введите параметры магнетрона:")
Ra = float(input("Радиус анода (в метрах, например 0.03): "))
Rk = float(input("Радиус катода (в метрах, например 0.01): "))
n = int(input("Число витков на метр (например 1000): "))
U1 = float(input("Минимальное напряжение (например 100): "))
U2 = float(input("Максимальное напряжение (например 1000): "))
U_test = float(input("Напряжение для построения траектории (например 500): "))

model = ElectronOrbitModel(Ra, Rk, n, U1, U2)
model.plot_orbit(U_test)
model.plot_current_vs_voltage()
