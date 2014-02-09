% ring_mod.m
% ECSE 490 - DSP Lab
% Group 1 - Isabel Helleur and Loren Lugosch
% Experiment 1 - February 6, 2013

%%% ring modulation %%%

%%% vector Y = vector X multiplied by a sine wave of frequency f0 %%%

%%% sample initialization of X %%%
X = wavread('PICCOLO.WAV');
% X = auread('chant.au');
Y = zeros(size(X));

%%% prepare the sine wave %%%
fs = 8192; % sampling rate for wav
duration = size(X,1)/fs; % length of song in seconds
T = 0:1/fs:duration;
f0 = 50;
S = 1 * sin(2*pi*f0*T);

%%% multiply each X element by corresponding S element, put in Y %%%
for i = 1:size(T,2)-1
    Y(i) = X(i)*S(i);
end

%sound(Y);
subplot(2,1,1), plot(abs(fft(X)));
title('Input signal');
axis([0 40000 0 600]);
subplot(2,1,2), plot(abs(fft(Y)));
title('Ring modulated signal');
axis([0 40000 0 600]);