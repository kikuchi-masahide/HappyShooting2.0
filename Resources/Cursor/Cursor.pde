PGraphics pg;

void setup()
{
  background(255,255,255,255);
  pg = createGraphics(20,20);
  pg.beginDraw();
  pg.background(0,0,0,0);
  pg.line(0,0,8,8);
  pg.line(8,12,0,20);
  pg.line(12,8,20,0);
  pg.line(12,12,20,20);
  pg.endDraw();
  
  size(20,20);
  image(pg,0,0);

  pg.save("cursor.png");
  
}

void draw()
{
}
