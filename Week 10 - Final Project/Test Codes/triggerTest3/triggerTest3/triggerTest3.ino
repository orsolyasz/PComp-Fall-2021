void setup() {
  // Start the serial port at 38.4K
  Serial1.begin( 38400 );

  // Set volume
  Serial1.print( "v" );
  Serial1.write( 0 ); // 0 = maximum volume, 255 = minimum volume
}

void loop() {
  // Loop from 1 to 5
  for ( int i = 1; i <= 4; i++ ) {
    // Play file i ( 1 to 5 )
    Serial1.print( "p" );
    Serial1.write( i );

    // Wait a bit
    delay( 1000 );
  }
}
