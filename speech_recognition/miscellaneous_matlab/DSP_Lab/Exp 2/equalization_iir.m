% channel impulse response needs to be the same length as s[n]
% so the first 200 values we get from samples 1000 to 1200
% and the rest of the values are zeroes

% read the signal
% filter it
% grab the channel impulse response
% make matrices have approp. dimensions
group1 = wavread('DSPLabG1.wav');
group1 = group1';

group1_clean = filter(IIR_butterworth_1450_1650, group1);

group1f = fft(group1_clean);
channel_imp = 1:length(group1);

for k = 1000:1199
    channel_imp(k-999) = 0.1*group1_clean(k);
end

for k = 200:length(group1);
    channel_imp(k) = 0;
end
% get channel transfer function by taking fft of impulse response
channel_tf = fft(channel_imp);

% divide channeled signal in frequency domain by channel transfer function
% get time domain signal from that
X = group1f./channel_tf;
dechanneled_signal = ifft(X);

% plot dechanneled signal
plot(dechanneled_signal);
title('IIR Filter - Fpass 1450Hz and Fstop 1650');