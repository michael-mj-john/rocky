void playerUpdate( void ) {

  int leftPlayer = leftSensor - leftNormal;
  int rightPlayer = rightSensor - rightNormal;

  // update left player
  if( leftPlayer < 100 ) { leftPixel = max(leftPixel - 1, 0 ); } 
  else {
    if( leftPlayer > 100 ) { leftPixel = min(leftPixel + 1, 119); }
    if( leftPlayer > 200 ) { leftPixel = min(leftPixel + 1, 119); }
    if( leftPlayer > 250 ) { leftPixel = min(leftPixel + 1, 119); }
  }

  // update right player
  if( rightPlayer < 100 ) { rightPixel = min(rightPixel +1, 119); }
  else {
    if( rightPlayer > 100 ) { rightPixel = max(rightPixel - 1, 0); }
    if( rightPlayer > 200 ) { rightPixel = max(rightPixel - 1, 0); }
    if( rightPlayer > 250 ) { rightPixel = max(rightPixel - 1, 0); }    
  }

  // 
  if( leftPixel >= rightPixel ) { 
    leftPlayer > rightPlayer ? rightPixel = leftPixel : leftPixel = rightPixel;
  }
}
