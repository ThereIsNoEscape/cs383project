struct frame
{
    double startTime;   //when the frame starts in milliseconds
    double interval;    //the length of the time in milliseconds
    rgb pixel[row][col];  //the rgb values for the frame
};
