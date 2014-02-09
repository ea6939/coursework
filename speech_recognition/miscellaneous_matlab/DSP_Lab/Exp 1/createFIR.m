% createFIR.m
% ECSE 490 - DSP Lab
% Group 1 - Isabel Helleur and Loren Lugosch
% Experiment 1 - February 6, 2013

% FIR comb filter with delay M %
% h[n] = delta[n] + Gdelta[n-M] %

% sample time range of interest from -5 to 5 %
T = 0:1:4000;
FIR = 1:numel(T);

% delay M and gain G (say 4000 (half second delay?), .5) %
M = 1000;
G = 1/4;
for i = 1:numel(T)
    if (i == 1)
        FIR(1) = 1;
    elseif (i == M + 1) % off by one
        FIR(M + 1) = G;
    else 
        FIR(i) = 0;
    end
end

stem(T,FIR);
axis([-1 5000 -1 2]);
