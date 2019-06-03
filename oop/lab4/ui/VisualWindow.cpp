#include <random>

#include "VisualWindow.h"

#define WIDTH 640
#define HEIGHT 320
#define SIDE 64
VisualWindow::VisualWindow(ObservableTenantService& service)
        : service{service} {
    QVBoxLayout* layout = new QVBoxLayout();
    setLayout(layout);
    resize(WIDTH, HEIGHT);

    service.subscribe(this);
}

int VisualWindow::getIntInRange(int start, int end) {
    std::random_device dev;
    std::mt19937 rng(dev());

    std::uniform_int_distribution<std::mt19937::result_type> range(start, end);

    return range(rng);
}

void VisualWindow::drawShape() {
    QPainter painter{this};

    int shape = getIntInRange(0, 3);
    int x = getIntInRange(0, WIDTH - SIDE);
    int y = getIntInRange(0, HEIGHT - SIDE);

    switch (shape) {
    case 0: {
        int side = getIntInRange(SIDE / 2, SIDE);
        const QPointF points[4] = {
            QPointF(x, y),
            QPointF(x + side, y),
            QPointF(x + side, y + side),
            QPointF(x, y + side),
        };

        painter.drawConvexPolygon(points, 4);
    }
        break;
    case 1: {
        int side = getIntInRange(SIDE / 2, SIDE);
        const QPointF points[3] = {
            QPointF(x - 0.866 * side, y - 0.5 * side),
            QPointF(x + 0.866 * side, y - 0.5 * side),
            QPointF(x + 0.0 * side, y + 1.0 * side),
        };

        painter.drawConvexPolygon(points, 3);
    }
        break;
    case 2: {
        int side = getIntInRange(SIDE / 2, SIDE);
        painter.drawEllipse(x, y, side, side);
    }
        break;
    case 3: {
        int side = getIntInRange(SIDE / 2, SIDE);
        int height = getIntInRange(SIDE / 2, SIDE);
        int discriminator = getIntInRange(SIDE / 8, SIDE / 4);

        const QPointF points[4] = {
            QPointF(x + discriminator, y),
            QPointF(x + side - discriminator, y),
            QPointF(x + side, y + height),
            QPointF(x, y + height),
        };

        painter.drawConvexPolygon(points, 4);
    }
        break;
    }
}

void VisualWindow::paintEvent(QPaintEvent* event) {
    if (event->type() != QEvent::Paint) {
        return;
    }

    std::vector<Tenant> tenants = service.getTenantsToNotify();
    for (int i = 0; i < tenants.size(); i++) {
        drawShape();
    }
}

void VisualWindow::receive(ObserveEvent event) {
    switch (event) {
    case ObserveEvent::CHANGE:
        refreshShapes();
        break;
    default:
        break;
    }
}

void VisualWindow::refreshShapes() {
    repaint();
}
