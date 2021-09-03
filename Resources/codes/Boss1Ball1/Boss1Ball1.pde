class Point{ //<>//
  public float x,y;
  public Point(float _x,float _y) {
    x = _x;
    y = _y;
  }
  public void plus(Point p) {
    x += p.x;
    y += p.y;
  }
  //this -= p;
  public void minus(Point p) {
    x -= p.x;
    y -= p.y;
  }
  //this *= f;
  public void times(float f) {
    x *= f;
    y *= f;
  }
  //|this|^2
  public float d2() {
    return x*x+y*y;
  }
  //|this|
  public float d() {
    return sqrt(x*x+y*y);
  }
  //90deg rotate
  public Point getrotate90() {
    Point p = new Point(-y,x);
    return p;
  }
}

Point plus(Point p1,Point p2) {
  Point p = new Point(p1.x+p2.x,p1.y+p2.y);
  return p;
}

Point minus(Point p1,Point p2) {
  Point p = new Point(p1.x-p2.x,p1.y-p2.y);
  return p;
}

Point times(Point p,float f) {
  Point c = new Point(p.x*f,p.y*f);
  return c;
}

float dot(Point p1,Point p2) {
  return p1.x*p2.x+p1.y*p2.y;
}

//if u and c are in the same area separated by the line going through l1 and l2
boolean isinsameside(Point u,Point l1,Point l2,Point c) {
  Point l1mc = minus(l1,c);
  Point l2mc = minus(l2,c);
  Point umc = minus(u,c);
  Point l1mcc = l1mc.getrotate90();
  Point l2mcc = l2mc.getrotate90();
  float a = (dot(umc,l2mcc))/(dot(l1mc,l2mcc));
  float b = (dot(umc,l1mcc))/(dot(l2mc,l1mcc));
  return (a+b <= 1);
}

void setup()
{
  float s = 20;
  Point p0 = new Point(0.0,0.0);
  Point p1 = new Point(2*s,s);
  Point p2 = new Point(s/2,s);
  Point c = new Point(s,s);
  background(255,255,255,255);
  PGraphics pg = createGraphics(40,40);
  pg.beginDraw();
  pg.background(0,0,0,0);
  pg.loadPixels();
  for(int x = 0;x < 2*s;x++) {
    for(int y = 0;y < s;y++) {
      Point p = new Point((float)x,(float)y);
      //not inside the triangle
      if(
        isinsameside(p,p0,p2,c) == false ||
        isinsameside(p,p0,p1,c) == false
      ) {
        pg.pixels[x+y*(int)s*2] = color(0,0,0,0);
      }else{
        float dpc = minus(p,c).d();
        float alpha = 255*dpc/s;
        pg.pixels[x+y*(int)s*2] = color(255,0,0,alpha);
      }
    }
  }
  for(int x = 0;x < 2*s;x++) {
    for(int y = (int)s;y < 2*s;y++) {
      int yy = 2*(int)s-y-1;
      pg.pixels[x+y*(int)s*2] = pg.pixels[x+yy*(int)s*2];
    }
  }
  pg.updatePixels();
  pg.endDraw();
  pg.save("test.png");
  size(40,40);
  image(pg,0,0);
}

void draw()
{
}
