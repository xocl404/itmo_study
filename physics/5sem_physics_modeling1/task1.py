import numpy as np
import matplotlib.pyplot as plt
from scipy.linalg import eigh_tridiagonal

def solve_schrodinger_1d(a, N, mass=1.0, hbar=1.0,
                         U_func=None, U_array=None,
                         n_states=4):

    x = np.linspace(0.0, a, N + 1)
    dx = x[1] - x[0]

    if U_array is not None:
        U = np.asarray(U_array)
        if len(U) != N + 1:
            raise ValueError("U_array должен иметь длину N+1")
    elif U_func is not None:
        U = U_func(x)
    else:
        raise ValueError("Нужно задать U_func или U_array")

    U_inner = U[1:-1]

    main_diag = (hbar**2 / (mass * dx**2)) + U_inner
    off_diag = -hbar**2 / (2 * mass * dx**2) * np.ones(N - 2)

    energies, psi_inner = eigh_tridiagonal(main_diag, off_diag)

    energies = energies[:n_states]
    psi_inner = psi_inner[:, :n_states].T

    psi = np.zeros((n_states, N + 1))
    for n in range(n_states):
        w = psi_inner[n]
        norm = np.sqrt(np.trapezoid(w**2, x[1:-1]))
        psi[n, 1:-1] = w / norm

    return x, U, energies, psi

def potential_parabolic(x, a, U0):
    return U0 * (x / a)**2

def potential_cosine(x, a, U0):
    return U0 * (1 - np.cos(2 * np.pi * x / a))

def potential_linear(x, a, U0):
    return U0 * (x / a)

def main():
    a = float(input("Введите ширину ямы a: "))
    N = int(input("Введите число узлов сетки N: "))
    mass = float(input("Введите массу m: "))
    hbar = float(input("Введите ħ: "))
    n_states = int(input("Сколько собственных состояний рассчитать?: "))

    print("\nВыберите тип потенциала:")
    print("1 — Параболическая яма  U(x) = U0 (x/a)^2")
    print("2 — Косинусная яма      U(x) = U0 (1 - cos(2πx/a))")
    print("3 — Линейная яма        U(x) = U0 (x/a)")
    print("4 — Табличная яма (ступенчатая)")

    pot_type = int(input("Введите номер варианта: "))

    if pot_type in [1, 2, 3]:
        U0 = float(input("Введите параметр U0: "))

    if pot_type == 1:
        U_func = lambda x: potential_parabolic(x, a, U0)
        U_array = None

    elif pot_type == 2:
        U_func = lambda x: potential_cosine(x, a, U0)
        U_array = None

    elif pot_type == 3:
        U_func = lambda x: potential_linear(x, a, U0)
        U_array = None

    elif pot_type == 4:
        U_func = None
        print("\nСтупенчатый потенциал (табличный):")
        U1 = float(input("U(x) слева (0 < x < a/3): "))
        U2 = float(input("U(x) в центре (a/3 < x < 2a/3): "))
        U3 = float(input("U(x) справа (2a/3 < x < a): "))

        x_temp = np.linspace(0, a, N + 1)
        U_array = np.zeros_like(x_temp)
        U_array[x_temp < a/3] = U1
        U_array[(x_temp >= a/3) & (x_temp < 2*a/3)] = U2
        U_array[x_temp >= 2*a/3] = U3

    else:
        print("Ошибка выбора!")
        return

    x, U, E, psi = solve_schrodinger_1d(a, N, mass, hbar,
                                        U_func=U_func,
                                        U_array=U_array,
                                        n_states=n_states)

    print("\nПервые собственные энергии:")
    for i, e in enumerate(E):
        print(f"E[{i}] = {e:.6f}")

    plt.figure(figsize=(10, 6))
    plt.plot(x, U, label="U(x)", linewidth=2)

    for n in range(n_states):
        plt.plot(x, psi[n] * 0.2 + E[n], label=f"ψ{n}")

    plt.grid()
    plt.xlabel("x")
    plt.ylabel("Энергия и волновые функции")
    plt.title("Потенциальная яма произвольной формы")
    plt.legend()
    plt.show()


if __name__ == "__main__":
    main()
