% channel impulse response needs to be the same length as s[n]
% so the first 200 values we get from samples 1000 to 1200
% and the rest of the values are zeroes

% read the signal
% make matrices have approp. dimensions
group1 = group1';

% filter the signal's noise
group1_clean = filter(LPF1550_1650, group1);

% get the channel impulse response by grabbing 200 values
channel_imp = 1:length(group1);
for i = 1000:1199
    channel_imp(i-999) = 0.1*group1_clean(i);
end

for i = 200:length(group1);
    channel_imp(i) = 0;
end

% get channel transfer function by taking fft of impulse response
channel_tf = fft(channel_imp);
inv_channel = ones(size(channel_tf))./channel_tf;

% divide channeled signal in frequency domain by channel transfer function
% get time domain signal from that
group1f = fft(group1_clean);
X = group1f./channel_tf;
dechanneled_signal = ifft(X);

%%
% plot dechanneled signal
% plot(abs(inv_channel));
% axis([0 2000 0 800]);
% title('Inverse of channel');

% plot(dechanneled_signal);
plot(original);