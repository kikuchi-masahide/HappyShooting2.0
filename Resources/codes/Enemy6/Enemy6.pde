PGraphics pg;

float PI = 3.141592;

float s = 40;

void setup()
{
  background(255,255,255,255);
  pg = createGraphics(800,800);
  pg.beginDraw();
  pg.background(0,0,0,0);
  pg.endDraw();
  
  for(int t = -30;t <= 30;t++)
  {
    PGraphics temp; //<>//
    temp = createGraphics(100,100);
    temp.beginDraw();
    temp.beginShape();
    float w = (0.75+0.25*sin(PI*t/60))*s;
    float h = 1.5*s-w;
    float x = 50;
    float y = 50;
    temp.vertex(x+w,y);
    temp.quadraticVertex(x,y+2*h,x-w,y);
    temp.quadraticVertex(x,y-2*h,x+w,y);
    temp.endShape();
    temp.strokeWeight(1);
    temp.fill(0,0,0,0);
    temp.endDraw();
    pg.beginDraw();
    int r = (t+30)%8;
    int c = (t+30)/8;
    pg.image(temp,r*100,c*100);
    pg.endDraw();
  }
  
  size(800,800);
  image(pg,0,0);

  pg.save("test.png");
  
}

void draw()
{
}
