import java.util.concurrent.TimeUnit;

/*
This small little program bounces a "ball" on four walls, without the use of if statements.
I implemented and "improved" (just some visually fancy stuff to make it prettier) some other codes in this work.
Made by Attila Fekete at the University of Debrecen in 2018
*/

public class Main {
	public static void main(String[] args){
		
		int width = 64 , height = 32;   //the resolution of the box
	    int x = 10, y = 10;   //current coordinates of the ball
	    int x1 = x, y1 = y;
	    
	    for(int i = 1; i < 200; i=i+0){
	    	try {
				TimeUnit.MILLISECONDS.sleep(75);
				System.out.print("\033[H\033[2J");
                System.out.flush();

                //move the ball
                x += Math.pow(-1, (x1-1)/(width-3));
                y += Math.pow(-1, (y1-1)/(height-3));
                x1++;;
                y1++;

                //upper wall
                for(i = 0; i < width; i++){ //simply draws a line from 0 to the desired width
                    System.out.print("#");
                }
                System.out.println("");

                //wall above the ball
                for(i = 0; i < y-1; i++){
                    System.out.print("#");
                    for(int j = 0; j < width-2; j++){   //draw the whitespaces just right before the desired width
                        System.out.print(" ");
                    }
                    System.out.println("#");
                }

                //line of the ball
                System.out.print(" ");    //shows the current x position of the ball visually (whitespace in the left wall)
                for(i = 0; i < x-1; i++){   //whitespaces left to the ball
                    System.out.print(" ");
                }
                System.out.print("@"); //the ball
                for(i = x+1; i < width-1; i++){ //whitespaces right to the ball
                    System.out.print(" ");
                }
                System.out.println("#"); //wall + line break

                //wall below the wall (nearly the same logic as with the wall above the ball)
                for(i = y; i < height-2; i++){
                    System.out.print("#");
                    for(int j = 0; j < width-2; j++){
                        System.out.print(" ");
                    }
                    System.out.println("#");
                }

                //bottom wall
                for(i = 0; i < x-1; i++){   //wall left to the ball
                    System.out.print("#");
                }
                System.out.print(" ");    //shows the current y position of the ball visually (whitespace in the left wall)
                for(i = x; i < width; i++){
                    System.out.print("#");
                }

                //cout << "\n\n" << "Coordinates:" << "\nx:" << x << " y: " << y << endl; //writes the current coordinates
                System.out.println("\nCoordinates:\nx:"+x+" y:"+y);

			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
	    }
	}
}

