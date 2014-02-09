image = imread('claire.tiff');
% image = imread('checkerboard.tiff');
stft = STFTmatrix(image,4);
% stft = stft(1:16,1:16);
% stft = STFT16(image,16);
mesh(abs(stft));