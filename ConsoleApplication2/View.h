#pragma once
//view
View levelView(Vector2f(0.0f, 0.0f), Vector2f(LEVEL_VIEW_HEIGHT, LEVEL_VIEW_HEIGHT));

View menuView(Vector2f(0.0f, 0.0f), Vector2f(LEVEL_VIEW_HEIGHT, LEVEL_VIEW_HEIGHT));

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
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(aspectRatio * LEVEL_VIEW_HEIGHT, LEVEL_VIEW_HEIGHT);
}
