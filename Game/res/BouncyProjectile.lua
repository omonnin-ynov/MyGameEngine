function update(deltaTime, parent, speed)
    rotation = parent:getRotation() * (math.pi / 180)
    directionX = math.sin(rotation) * speed * deltaTime
    directionY = -1 * math.cos(rotation) * speed * deltaTime
    direction = sf.Vector2f (directionX, directionY)
    parent:move(direction)
end