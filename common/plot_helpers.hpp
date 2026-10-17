#pragma once

#include <gnuplot-iostream.h>

#include <Eigen/Dense>
#include <string>
#include <vector>

namespace plot {

// диапазон значений для оси (от min до max)
struct Range {
    double min;
    double max;
};

// создает интерактивное окно gnuplot
inline Gnuplot make_interactive() {
    return Gnuplot("gnuplot");
}

// настраивает qt-терминал, заголовок, сетку и оси
inline void setup_interactive(Gnuplot &gp, const std::string &title) {
    gp << "set terminal qt enhanced\n";
    gp << "set title '" << title << "'\n";
    gp << "set grid\n";
    gp << "set size square\n";
    gp << "set zeroaxis\n";
}

// устанавливает диапазоны для осей X и Y
inline void setup_ranges(Gnuplot &gp, Range x, Range y) {
    gp << "set xrange [" << x.min << ":" << x.max << "]\n";
    gp << "set yrange [" << y.min << ":" << y.max << "]\n";
}

// общий каркас: открывает окно, настраивает его, рисует (через body) и ждет закрытия
template <typename Body>
inline void run_plot(const std::string &window_title, Range x, Range y, Body body) {
    Gnuplot gp = make_interactive();
    setup_interactive(gp, window_title);
    setup_ranges(gp, x, y);
    body(gp);
    gp << "pause mouse close\n";
}

// --- Рисование ---

// рисует один 2D-вектор из начала координат
inline void draw_vector(Gnuplot &gp, const Eigen::Vector2d &v,
                        const std::string &title = "vector") {
    gp << "plot '-' with vectors filled head title '" << title << "'\n";
    gp.send1d(std::vector<std::vector<double>>{{0.0, 0.0, v(0), v(1)}});
}

// рисует два 2D-вектора из начала координат
inline void draw_two_vectors(Gnuplot &gp, const Eigen::Vector2d &a, const Eigen::Vector2d &b,
                             const std::string &title_a, const std::string &title_b) {
    gp << "plot '-' with vectors filled head title '" << title_a
       << "', '-' with vectors filled head title '" << title_b << "'\n";
    gp.send1d(std::vector<std::vector<double>>{{0.0, 0.0, a(0), a(1)}});
    gp.send1d(std::vector<std::vector<double>>{{0.0, 0.0, b(0), b(1)}});
}

// --- обертки ---

// показывает один вектор из начала координат в новом окне
inline void show_vector(const Eigen::Vector2d &v, const std::string &title,
                        const std::string &window_title, Range x, Range y) {
    run_plot(window_title, x, y, [&](Gnuplot &gp) { draw_vector(gp, v, title); });
}

// показывает два вектора из начала координат в новом окне
inline void show_two_vectors(const Eigen::Vector2d &a, const Eigen::Vector2d &b,
                             const std::string &title_a, const std::string &title_b,
                             const std::string &window_title, Range x, Range y) {
    run_plot(window_title, x, y,
             [&](Gnuplot &gp) { draw_two_vectors(gp, a, b, title_a, title_b); });
}

// показывает 4 вектора ортогонального разложения (все из начала координат)
inline void show_orthogonal_decomposition(const Eigen::Vector2d &t, const Eigen::Vector2d &r,
                                          const std::string &window_title, Range x, Range y) {
    run_plot(window_title, x, y, [&](Gnuplot &gp) {
        const double denom = r.squaredNorm();
        if (denom == 0.0)
            return;

        const Eigen::Vector2d t_parallel = (t.dot(r) / denom) * r;
        const Eigen::Vector2d t_perp = t - t_parallel;

        gp << "plot '-' with vectors filled head lc 'black' lw 3 title 't', "
           << "'-' with vectors filled head lc 'gray' lw 3 title 'r', "
           << "'-' with vectors nohead lc 'black' dt 2 lw 3 title 't‖', "
           << "'-' with vectors nohead lc 'black' dt 3 lw 3 title 't⟂'\n";

        gp.send1d(std::vector<std::vector<double>>{{0.0, 0.0, t(0), t(1)}});
        gp.send1d(std::vector<std::vector<double>>{{0.0, 0.0, r(0), r(1)}});
        gp.send1d(std::vector<std::vector<double>>{{0.0, 0.0, t_parallel(0), t_parallel(1)}});
        gp.send1d(std::vector<std::vector<double>>{{0.0, 0.0, t_perp(0), t_perp(1)}});
    });
}

// показывает сложение векторов «хвост к голове» (v, затем w из конца v)
inline void show_tail_to_head(const Eigen::Vector2d &v, const Eigen::Vector2d &w,
                              const std::string &window_title, Range x, Range y) {
    run_plot(window_title, x, y, [&](Gnuplot &gp) {
        const Eigen::Vector2d sum = v + w;
        gp << "plot '-' with vectors filled head title 'v', "
           << "'-' with vectors filled head title 'w', "
           << "'-' with vectors filled head title 'v + w'\n";
        gp.send1d(std::vector<std::vector<double>>{{0.0, 0.0, v(0), v(1)}});
        gp.send1d(std::vector<std::vector<double>>{{v(0), v(1), w(0), w(1)}});
        gp.send1d(std::vector<std::vector<double>>{{0.0, 0.0, sum(0), sum(1)}});
    });
}

// показывает сумму и разность двух векторов (a, b, a+b, a-b)
inline void show_sum_and_diff(const Eigen::Vector2d &a, const Eigen::Vector2d &b,
                              const std::string &window_title, Range x, Range y) {
    run_plot(window_title, x, y, [&](Gnuplot &gp) {
        const Eigen::Vector2d sum = a + b;
        const Eigen::Vector2d diff = a - b;
        gp << "plot '-' with vectors filled head title 'a', "
           << "'-' with vectors filled head title 'b', "
           << "'-' with vectors filled head title 'a + b', "
           << "'-' with vectors nohead title 'a - b'\n";
        gp.send1d(std::vector<std::vector<double>>{{0.0, 0.0, a(0), a(1)}});
        gp.send1d(std::vector<std::vector<double>>{{0.0, 0.0, b(0), b(1)}});
        gp.send1d(std::vector<std::vector<double>>{{0.0, 0.0, sum(0), sum(1)}});
        gp.send1d(std::vector<std::vector<double>>{{b(0), b(1), diff(0), diff(1)}});
    });
}

// показывает проекцию v на onto и перпендикуляр (v - proj) пунктиром от проекции к v
inline void show_projection_with_onto(const Eigen::Vector2d &v, const Eigen::Vector2d &onto,
                                      const std::string &window_title, Range x, Range y) {
    run_plot(window_title, x, y, [&](Gnuplot &gp) {
        const double denom = onto.squaredNorm();
        if (denom == 0.0)
            return;

        const Eigen::Vector2d proj = (v.dot(onto) / denom) * onto;
        const Eigen::Vector2d error = v - proj;

        gp << "plot '-' with vectors filled head title 'a', "
           << "'-' with vectors filled head title 'b', "
           << "'-' with vectors filled head title 'projection (βa)', "
           << "'-' with vectors nohead dashtype 2 title '(b - βa)'\n";

        gp.send1d(std::vector<std::vector<double>>{{0.0, 0.0, onto(0), onto(1)}});
        gp.send1d(std::vector<std::vector<double>>{{0.0, 0.0, v(0), v(1)}});
        gp.send1d(std::vector<std::vector<double>>{{0.0, 0.0, proj(0), proj(1)}});
        gp.send1d(std::vector<std::vector<double>>{{proj(0), proj(1), error(0), error(1)}});
    });
}

}  // namespace plot