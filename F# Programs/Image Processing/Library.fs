//	
// F# image processing functions.
//
// More details?
//
// Name? School? Date?
// **--------------------	----------------------
// #     Project 3 – Image processing
// #     Course: CS 341, Spring 2024.
// #     System: Codio IDE 2024
// #     Author: Alejandro Bravo   
// #     Date: 3/10/2024
// #  ---------------------------------------------**/
//

namespace ImageLibrary

module Operations =
  //
  // all functions must be indented
  //

  //
  // Sepia:
  //
  // Applies a sepia filter onto the image and returns the 
  // resulting image as a list of lists. 
  // The sepia filter adjusts the RGB values of each pixel
  // headording to the following formulas:
  //    newRed = 0.393*origRed + 0.769*origGreen + 0.189*origBlue
  //    newGreen = 0.349*origRed + 0.686*origGreen + 0.168*origBlue
  //    newBlue = 0.272*origRed + 0.534*origGreen + 0.131*origBlue
  // We will use truncation to cast from the floating point result 
  // to the integer value.
  // 
  // If any of these values exceed 255, then 255 should be used
  // instead for that value.
  //
  // Returns: updated image.
  //

  let updateValues (r, g, b) =
    let newRed = int (0.393 * float(r) + 0.769 * float(g) + 0.189 * float(b))//converts based on formulas given and converts to int
    let newGreen = int (0.349 * float(r) + 0.686 * float(g) + 0.168 * float(b))
    let newBlue = int (0.272 * float(r) + 0.534 * float(g) + 0.131 * float(b))
    let newRed = if newRed > 255 then 255 else newRed //makes sure they stay within the bounds 
    let newGreen = if newGreen > 255 then 255 else newGreen
    let newBlue = if newBlue > 255 then 255 else newBlue
    (newRed, newGreen, newBlue)//returns list with new values

  let rec Sepia (width:int) 
                    (height:int) 
                    (depth:int) 
                    (image:(int*int*int) list list) = 
    image |> List.map (fun row -> row |> List.map(updateValues))//updates values and stores into new list



  //
  // Increase Intensity
  //
  // Increase the intensity of a particular RGB channel
  // headording to the values of the parameters.
  // The intensity is the scaling factor by which the
  // channel selected should be increased (or decreased 
  // if the value is less than 1).
  // The channel is one of 'r', 'g', or 'b' which 
  // correspond to red, green, and blue respectively.
  // If the channel is not one of those three values,
  // do not modify the image.
  // Remember that the maximum value for any pixel 
  // channel is 255, so be careful of overflow!
  //
  // Returns: updated image.
  //

  let rec IncreaseIntensity (width:int) (height:int) (depth:int) (image:(int*int*int) list list) (intensity:double) (channel:char) =
    let changeIntensity (r, g, b) = //helper function that changes the intensity
        let newIntensity pixel = //function to keep within bounds
            let newValue = int (float(pixel) * intensity)//turns intensity to int and multiplies based on how much wanted
            if newValue > 255 then 255 else newValue //makes sure we stay within 255

        if channel = 'r' then//applies intensity to red if wanted
            (newIntensity r, g, b)//applies intensity to red
        elif channel = 'g' then//applies intensity to green if wanted
            (r, newIntensity g, b)//applies intensity to green
        elif channel = 'b' then//applies intensity to blue if wanted
            (r, g, newIntensity b)//applies intensity to blue
        else
            (r, g, b) //else value is above 255 so don't change 
    image |> List.map (fun row -> row |> List.map(changeIntensity))//goes through list and adjusts Intensity


  //
  // FlipHorizontal:
  //
  // Flips an image so that what’s on the left is now on 
  // the right, and what’s on the right is now on the left. 
  // That is, the pixel that is on the far left end of the
  // row ends up on the far right of the row, and the pixel
  // on the far right ends up on the far left. This is 
  // repeated as you move inwards toward the row's center.
  //
  // Returns: updated image.
  //
  let rec FlipHorizontal (width:int)
                         (height:int)
                         (depth:int)
                         (image:(int*int*int) list list) = 
    image |> List.map(List.rev)//stores list into a new list after flipping the elements in reverse order which in this case flips horizontal


  //
  // Rotate180:
  //
  // Rotates the image 180 degrees.
  //
  // Returns: updated image.
  //
  let rec Rotate180 (width:int)
                        (height:int)
                        (depth:int)
                        (image:(int*int*int) list list) = 
    let newImage =  List.rev(image) |> List.map(List.rev) //90 degree horizontal flip then a 90 degree vertical flip
    newImage

 
  //
  // Edge Detection:
  //
  // Edge detection is an algorithm used in computer vision to help
  // distinguish different objects in a picture or to distinguish an
  // object in the foreground of the picture from the background.
  //
  // Edge Detection replaces each pixel in the original image with
  // a black pixel, (0, 0, 0), if the original pixel contains an 
  // "edge" in the original image.  If the original pixel does not
  // contain an edge, the pixel is replaced with a white pixel 
  // (255, 255, 255).
  //
  // An edge occurs when the color of pixel is "significantly different"
  // when compared to the color of two of its neighboring pixels. 
  // We only compare each pixel in the image with the 
  // pixel immediately to the right of it and with the pixel
  // immediately below it. If either pixel has a color difference
  // greater than a given threshold, then it is "significantly
  // different" and an edge occurs. Note that the right-most column
  // of pixels and the bottom-most column of pixels can not perform
  // this calculation so the final image contain one less column
  // and one less row than the original image.
  //
  // To calculate the "color difference" between two pixels, we
  // treat the each pixel as a point on a 3-dimensional grid and
  // we calculate the distance between the two points using the
  // 3-dimensional extension to the Pythagorean Theorem.
  // Distance between (x1, y1, z1) and (x2, y2, z2) is
  //  sqrt ( (x1-x2)^2 + (y1-y2)^2 + (z1-z2)^2 )
  //
  // The threshold amount will need to be given, which is an 
  // integer 0 < threshold < 255.  If the color distance between
  // the original pixel either of the two neighboring pixels 
  // is greater than the threshold amount, an edge occurs and 
  // a black pixel is put in the resulting image at the location
  // of the original pixel. 
  //
  // Returns: updated image.
  //

  

  let distance (r1, g1, b1) (r2, g2, b2) = //gets distance between the two points
    let red = float(r1 - r2) //gets red distance
    let green = float(g1 - g2) //gets green distance
    let blue = float(b1 - b2) //gets blue distance
    sqrt (red * red + green * green + blue * blue)//computes distance

  let EdgeDetect (width:int)
                     (height:int)
                     (depth:int)
                     (image:(int*int*int) list list)
                     (threshold:int) = 

    let isEdge point rightPixel bottomPixel = //checks if the pixel is a edge
        distance point rightPixel > float(threshold) || distance point bottomPixel > float(threshold) //checks if right pixel or bottom is greater then threshold

    let rec compareRow row currentRow head = //recursively goes through the list to compare right and bottom neighbors
        match row, currentRow with
        | (point :: rightNeighbor :: _), (bottomPixel :: _) :: _ -> //breaks up the point 
            if isEdge point rightNeighbor bottomPixel then //checks if the current pixel is a edge
                compareRow (List.tail row) (List.map List.tail currentRow) ((0, 0, 0) :: head)//then it changes the pixels to dark
            else 
                compareRow (List.tail row) (List.map List.tail currentRow) ((255, 255, 255) :: head)//if its a neighbor and doesnt exceed threshold then we change color to black
        | _ -> List.rev head

    let rec changeColor image head = //function that recursively goes through rows and changes color
        match image with
        | row1 :: row2 :: tail -> //deconstrcuts image list
            let row = compareRow row1 (row2 :: tail) []//compares the rows and makes sure theyre edges and changes color
            changeColor (row2 :: tail) (row :: head)//goes to next element 
        | _ -> List.rev head//reverse list so its back to original order

    changeColor image []//returns image with new color 

      