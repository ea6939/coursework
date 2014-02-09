% allpass.m
% ECSE 490 - DSP Lab
% Group 1 - Isabel Helleur and Loren Lugosch
% Experiment 1 - February 6, 2013

a = 5;
b = 100;
%when a is smaller theres a less than unity reverb
%when b is smaller the impulse response has components that are amplified
%10^5 as much 
num = [a b];
den = [b a];

%fvtool(num, den);
X = wavread('ORCHORG.wav');
Y = filter(num, den, X);
fvtool(num, den);
% Z = filter(num, den, Y);
% W = filter(num, den, Z);
% subplot(2,1,1), plot(X);
% subplot(2,1,2), plot(W);
% fvtool(num, den);
% sound(W, 16000);