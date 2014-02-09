% createIIR.m
% ECSE 490 - DSP Lab
% Group 1 - Isabel Helleur and Loren Lugosch
% Experiment 1 - February 6, 2013

% IIR comb filter with delay M, pseudo infinite %
% h[n] = delta[n] + Gdelta[n-M] %

% sample time range of interest from -5 to 5 %
T = 0:1:10000;
IIR = 1:numel(T);

% delay M and gain G 
M = 1000;
G = 3/4;
exponent=1;

for i = 1:numel(T)
    if (i == 1)
        IIR(1) = 1;
    elseif (mod(i,M + 1)==0) % off by one
        IIR(i) = G^exponent;
        exponent = exponent + 1;
    else 
        IIR(i) = 0;
    end
end

stem(T,IIR);
axis([-1 11000 -1 2]);
