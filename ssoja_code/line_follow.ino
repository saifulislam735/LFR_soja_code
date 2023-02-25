void line_follow() {
  while (1) { //infinite loop
    reading();
    if (sum == 0) {
      if (flag != 's') {
        if (flag != 't') {//we already moved a little forward when sensor was on 'T' section...no need to move forward further!
          motor(10 * spl, 10 * spr);
          delay(30); //time given to move robot forward for a certain amount of time to adjust itself in 90 degree line.
        }
        if (flag == 'l') {
          motor(-4 * spl, 4 * spr);
          while (s[2] == 0 && s[3] == 0) reading();
        }
        else if (flag == 'r') {
          motor(4* spl, -4* spr);
          while (s[2] == 0 && s[3] == 0) reading();
        }
        else if (flag == 't') {
          motor(4* spl, -4 * spr); //make your choice if you want to go left or right in T section
          while (s[2] == 0 && s[3] == 0) reading();
        }
        flag = 's'; //when you are done turning robot, make the flag to its normal state so that robot wont turn on its own when it finds no line without detecting 90degree logic
      }
    }
    else if (sum == 1 || sum == 2) {  //only for straight line
      if (sensor == 0b001100) {
        if (pos != 0) {
          (pos == 1) ? motor(-10 * spl, 10 * spr) : motor(10 * spl, -10 * spr);
          delay(10); pos = 0;  //this logic is for those whose bot is wabbling during high speed run. this logic will forcefully return bot to its midpoint. don't give more than 30ms delay here!
        }
        motor(10 * spl, 10 * spr);
      }
      //right side portion
      else if (sensor == 0b000100) motor(10 * spl, 9 * spr); 
      else if (sensor == 0b000110) {
        pos = 1; motor(10 * spl, 6 * spr);
      }
      else if (sensor == 0b000010) {
        pos = 1; motor(10 * spl, 3 * spr);
      }
      else if (sensor == 0b000011) {
        pos = 1; motor(10 * spl, 0 * spr);
      }
      else if (sensor == 0b000001) {
        pos = 1;
        motor(10 * spl, -3 * spr);
      }
      //left side portion
      else if (sensor == 0b001000) motor(9 * spl, 10 * spr);
      else if (sensor == 0b011000) {
        pos = -1; motor(6 * spl, 10 * spr);
      }
      else if (sensor == 0b010000) {
        pos = -1; motor(3 * spl, 10 * spr);
      }
      else if (sensor == 0b110000) {
        pos = -1; motor(0 * spl, 10 * spr);
      }
      else if (sensor == 0b100000) {
        pos = -1; motor(-3 * spl, 10 * spr);
      }
    }

    else if ((sum == 3 || sum == 4 || sum == 5) && flag != 't') { //only for sharp turn logic
      if (sensor == 0b101100 || sensor == 0b100110 || sensor == 0b110100){delay(50); flag = 'l';}
      else if (sensor == 0b001101 || sensor == 0b011001 || sensor == 0b001011){delay(50); flag = 'r';}
      else if (sensor == 0b111100 || sensor == 0b111000 || sensor == 0b111110){delay(50); flag = 'l';}
      else if (sensor == 0b001111 || sensor == 0b000111 || sensor == 0b011111){delay(50); flag = 'r';}
    }

    else if (sum == 6) {
      delay(100);
      reading();
      if (sum == 6) { //stop point detection
        motor(0, 0);
        while (sum == 6) reading();
        delay(1000);
      }
      else if(sum == 0) flag = 't';
      else flag = 's'; //if the robot detects straight line going a bit forward, no need to keep previous flag value. it should just keep moving forward
    }
  }
}
