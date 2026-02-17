import numpy as np
import matplotlib.pyplot as plt

def transmission(E, x, U, mass=1.0, hbar=1.0):
    dx = x[1] - x[0]
    psi = np.zeros_like(x, dtype=complex)
    psi[0] = 0
    psi[1] = 1e-6
    for i in range(1, len(x)-1):
        k2 = 2*mass*(E - U[i]) / hbar**2
        psi[i+1] = (2 - dx*dx*k2)*psi[i] - psi[i-1]
    k_left = np.sqrt(max(2*mass*E/hbar**2, 0))
    k_right = np.sqrt(max(2*mass*E/hbar**2, 0))
    T = abs(psi[-1])**2 * (k_right / k_left)
    return T

def rectangular_barrier(x, h, U0):
    return np.where((x >= 0) & (x <= h), U0, 0)

def linear_barrier(x, h, U0):
    return np.where((x >= 0) & (x <= h), U0 * (x / h), 0)

def cosine_barrier(x, h, U0):
    return np.where((x >= 0) & (x <= h), U0*(1 - np.cos(np.pi*x/h))/2, 0)

def main():
    
    h = float(input("Введите ширину барьера h: "))
    N = int(input("Введите число узлов сетки N: "))
    mass = float(input("Введите массу m: "))
    hbar = float(input("Введите ħ: "))
    print()

    print("Выберите форму барьера:")
    print("1 — прямоугольный")
    print("2 — линейный")
    print("3 — косинусный")
    print("4 — табличный (две ступени)")
    pot = int(input("Тип: "))

    x = np.linspace(-h, 2*h, N)

    if pot == 1:
        U0 = float(input("Введите высоту барьера U0: "))
        U = rectangular_barrier(x, h, U0)

    elif pot == 2:
        U0 = float(input("Введите максимальное значение U0: "))
        U = linear_barrier(x, h, U0)

    elif pot == 3:
        U0 = float(input("Введите максимальное значение U0: "))
        U = cosine_barrier(x, h, U0)

    elif pot == 4:
        U1 = float(input("Введите левую ступень U1: "))
        U2 = float(input("Введите правую ступень U2: "))
        U = np.zeros_like(x)
        U[(x >= 0) & (x < h/2)] = U1
        U[(x >= h/2) & (x <= h)] = U2

    else:
        print("Ошибка выбора")
        return

    E_values = np.linspace(0.01, max(U) * 2, 400)
    T_values = [transmission(E, x, U, mass, hbar) for E in E_values]

    plt.figure(figsize=(10, 6))
    plt.plot(E_values, T_values)
    plt.xlabel("E")
    plt.ylabel("T(E)")
    plt.title("Коэффициент прохождения через барьер")
    plt.grid()
    plt.show()


if __name__ == "__main__":
    main()
