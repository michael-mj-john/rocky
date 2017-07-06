void ledUpdate ( void ) {

  if(gameState == PREP)
  {    
    // if a button has been pressed, stop flashing
    if(leftNormal != 0) strand.setPixelColor(0, 255, 0, 0);
    if(rightNormal != 0) strand.setPixelColor(119, 0, 255, 0);
    
    // flash pixels at each end
    if(flashOn)
    {
      if(leftNormal == 0) strand.setPixelColor( 0, 0, 0, 255 ); 
      if(rightNormal == 0) strand.setPixelColor( 119, 0, 0, 255);
      flashOn = 0; 
    } else  { 
      if(leftNormal == 0) strand.setPixelColor( 0, 0, 255, 255 ); 
      if(rightNormal == 0) strand.setPixelColor(119, 0, 255, 255);
      flashOn = 1; 
    }

    for(int i = 1; i < 119; ++i) strand.setPixelColor(i, 0, 0, 0);
  }
  else if (gameState == PLAY)
  {
    for(int i = 0; i <= leftPixel; ++i) { strand.setPixelColor(i, 255, 0, 0); } // left player
    for(int i = 119; i >= rightPixel; --i) { strand.setPixelColor(i, 0, 255, 0); } // right player
  
    if(leftPixel == rightPixel) { strand.setPixelColor(leftPixel, 255, 255, 255); } // white pixel where left and right meet
    for(int i = leftPixel + 1; i < rightPixel; ++i) { strand.setPixelColor(i, 0, 0, 0); } // clear middle pixels 
  }
  else if (gameState == POST)
  {
    for(int i = 0; i < 6; ++i) 
    {
      if(flashOn)
      {
        if(leftPixel == 119) //left side wins 
        {
          for(int j = 0; j < 119; ++j) strand.setPixelColor(j, 255, 0, 0);
        } 
        else if (rightPixel == 0) //right side wins
        {
          for(int j = 0; j < 119; ++j) strand.setPixelColor(j, 0, 255, 0);
        }
        flashOn = 0;
      }
      else
      {
        for(int j = 0; j < 119; ++j) strand.setPixelColor(j, 0, 0, 0);
        flashOn = 1;
      }
      strand.show();
      delay(400);
    }   
  }
}

