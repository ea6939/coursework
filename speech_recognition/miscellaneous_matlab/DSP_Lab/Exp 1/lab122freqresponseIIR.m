 % Gain
G = 3/4;

numerator = [1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
denominator = [1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 G];
freqz(numerator, denominator);
