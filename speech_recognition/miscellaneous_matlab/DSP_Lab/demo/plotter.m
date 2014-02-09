group1 = wavread('NoisySig.wav');
original = wavread('CleanSig.wav');

noise = 2*randn(size(group1));
group1 = group1 + noise;

equalization
subplot(2,1,1), plot(original);
axis([1200 1520 -1.2 1.2]);

subplot(2,1,2), plot(dechanneled_signal);
axis([1200 1520 -1.2 1.2]);