#pragma once
//view
View levelView(Vector2f(0.0f, 0.0f), Vector2f(LEVEL_VIEW_HEIGHT, LEVEL_VIEW_HEIGHT));
View menuView(Vector2f(0.0f, 0.0f), Vector2f(LEVEL_VIEW_HEIGHT, LEVEL_VIEW_HEIGHT));

void checkViewIntersect(View& view, const Vector2u& levelSize)
{
    Vector2f viewCenter = view.getCenter();
    Vector2f viewSize = view.getSize();

    if (viewCenter.x - viewSize.x / 2.0f < 0) 
    {
        viewCenter.x = viewSize.x / 2.0f;
    }
    if (viewCenter.x + viewSize.x / 2.0f > levelSize.x) 
    {
        viewCenter.x = levelSize.x - viewSize.x / 2.0f;
    }
    if (viewCenter.y - viewSize.y / 2.0f < 0) 
    {
        viewCenter.y = viewSize.y / 2.0f;
    }
    if (viewCenter.y + viewSize.y / 2.0f > levelSize.y) 
    {
        viewCenter.y = levelSize.y - viewSize.y / 2.0f;
    }

    if (viewSize.x > levelSize.x)
    {
        viewSize.x = levelSize.x;
    }
    if (viewSize.y > levelSize.y)
    {
        viewSize.y = levelSize.y;
    }

    view.setSize(viewSize);
    view.setCenter(viewCenter);
}

void updateView(View& view, const Vector2f& viewColliderPosition, const Vector2u& levelSize)
{
    view.setCenter(viewColliderPosition);
    checkViewIntersect(view, levelSize);
}

void changeViewZoom(View& view) 
{
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
