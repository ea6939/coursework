% different bit error rates
BER = [0 0 0 0];
inverse_variance = [0 1/1.1 1/2 1/4];

% first use clean and noisy
% clear;
group1 = wavread('NoisySig.wav');
original = wavread('CleanSig.wav');
equalization;
bitcounter;
'no added noise'
BER(1) = bit_error_rate % print

% add noise to noisy signal
% clear;
group1 = wavread('NoisySig.wav');
original = wavread('CleanSig.wav');
noise = 1.1*randn(size(group1));
group1 = group1 + noise;
equalization;
bitcounter;
'variance = 1.1'
BER(2) = bit_error_rate % print
plot(group1);

% add noise to noisy signal
% clear;
group1 = wavread('NoisySig.wav');
original = wavread('CleanSig.wav');
noise = 2*randn(size(group1));
group1 = group1 + noise;
equalization;
bitcounter;
'variance = 2'
BER(3) = bit_error_rate % print
plot(group1);

% add noise to noisy signal
% clear;
group1 = wavread('NoisySig.wav');
original = wavread('CleanSig.wav');
noise = 4*randn(size(group1));
group1 = group1 + noise;
equalization;
bitcounter;
'variance = 4'
BER(4) = bit_error_rate % print
plot(group1);

plot(1./inverse_variance, BER);