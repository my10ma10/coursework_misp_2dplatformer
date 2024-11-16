#pragma once
//view
View view(Vector2f(0.0f, 0.0f), Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));


void changeViewZoom(View& view) {
    if (Keyboard::isKeyPressed(Keyboard::Equal)) {
        view.zoom(0.995f);
    }
    if (Keyboard::isKeyPressed(Keyboard::Dash)) {
        view.zoom(1.005f);
    }
}

void changeViewAspectRatio(const RenderWindow& window, View& view)
{
    float aspect_ratio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(aspect_ratio * VIEW_HEIGHT, VIEW_HEIGHT);
}
