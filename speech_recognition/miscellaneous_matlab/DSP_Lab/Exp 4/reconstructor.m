% analysis synthesis script

% test_signal = square(1:1/100:10);
% test_signal = sin(1:1/100:10);
test_signal = wavread('ORCHORG.WAV');
% test_signal = sawtooth(1:1/100:10);

% filter_bank = 'filtersCMFB.mat';
filter_bank = 'filtersLOT.mat';

% convolve the signal with each filter and FFT each subband
A = analysis_bank(test_signal,filter_bank);

% downsample each subband
Y = downsample_bank(A);

% try 16 levels in last two subbands, then 8 levels
% try 64 levels in the first subband, then 32, then 16
levels = [64 32 32 32 32 32 32 32];
Q = quantizer_bank_nonuniform(Y,levels);

% upsample each subband
B = upsample_bank(Q);

% IFFT each subband
Xhat_bank = synthesis_bank(B,filter_bank);

% add columns of subband matrix to get reconstructed output
for n = 1:length(Xhat_bank(1,:))
    Xhat(n) = sum(Xhat_bank(:,n));
end

% calculate SNRs
signal_power = sum(abs(fft(test_signal)).^2)/length(test_signal);
noise_power = 1;

% calculate entropies
entropy_of_subband = zeros([1 length(levels)]);
for n=1:length(levels)
    entropy_of_subband(n) = entropy_calculator(Q(n,:),32);
end
