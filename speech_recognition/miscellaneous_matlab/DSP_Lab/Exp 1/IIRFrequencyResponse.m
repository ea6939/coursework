% IIRFrequencyResponse.m
% ECSE 490 - DSP Lab
% Group 1 - Isabel Helleur and Loren Lugosch
% Experiment 1 - February 6, 2013

% Gain
G = 3/4;

numerator = [1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
denominator = [1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 G];
freqz(numerator, denominator);
