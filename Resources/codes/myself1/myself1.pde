PGraphics pg;


void setup()
{
  background(255,255,255,255);
  pg = createGraphics(80,80);
  
  float size = 40;
  float[] xarr=new float[8];
  float[] yarr=new float[8];
  for(int i=0;i<8;i++)
  {
    xarr[i] = size+size*cos(PI/2*i);
    yarr[i] = size+size*sin(PI/2*i);
  }
  fill(0,0,0,255);
  for(int i = 0;i < 4;i++)
  {

    beginShape(TRIANGLES);
    vertex(xarr[i],yarr[i]);
    vertex((xarr[i]+xarr[i+1])/2,(yarr[i]+yarr[i+1])/2);
    vertex((xarr[i]+xarr[i+3])/2,(yarr[i]+yarr[i+3])/2);
    endShape();
    
    /*triangle(
    xarr[i],yarr[i],
    (xarr[i]+xarr[i+1])/2,(yarr[i]+yarr[i+1])/2,
    (xarr[i]+xarr[i+3])/2,(yarr[i]+yarr[i+3])/2    
    );*/
    
  }
  ellipse(size,size,size/20,size/20);


  pg.endDraw();
  
  size(80,80);
  image(pg,0,0);

  pg.save("myself1.png");
  
}

void draw()
{
}
