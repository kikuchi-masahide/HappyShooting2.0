PGraphics pg;
PFont font;

void setup()
{
  background(255,255,255,255);
  pg = createGraphics(300,30);
  pg.beginDraw();
  pg.background(0,0,0,0);
  pg.textAlign(CENTER,CENTER);
  pg.textSize(30);
  pg.fill(0,0,0,255);
  font = loadFont("MS-PGothic-30.vlw");
  pg.textFont(font,30);
  pg.text("Happy Shooting",150,15);
  pg.endDraw();
  
  size(300,30);
  image(pg,0,0);

  pg.save("test.png");
  
}

void draw()
{
}
