% bit counter

bitrate = 10;

start_sample = 1200;
stop_sample = 1520;
total_bits = (stop_sample-start_sample)/bitrate;

bits_clean = 0*(1:total_bits);
bits_noisy = 0*(1:total_bits);
number_of_ones = 0;
number_of_zeros = 0;

sample_2 = start_sample + 2;
sample_7 = start_sample + 7;

% assume filtering and dechanneling have already happened
% first, count bits in clean version
counted_signal = original;

for iterator = 1:total_bits
    if (counted_signal(sample_2) > 0) && (counted_signal(sample_7) > 0)
        bits_clean(iterator) = 0;
    elseif (counted_signal(sample_2) < 0) && (counted_signal(sample_7) < 0)
        bits_clean(iterator) = 0;
    else
        bits_clean(iterator) = 1;
    end
    
    % move to next bit
    sample_2 = sample_2 + 10;
    sample_7 = sample_7 + 10;
end

% next count bits in noisy version
sample_2 = start_sample + 2;
sample_7 = start_sample + 7;
counted_signal = dechanneled_signal;

for iterator = 1:total_bits
    if (counted_signal(sample_2) > 0) && (counted_signal(sample_7) > 0)
        bits_noisy(iterator) = 0;
    elseif (counted_signal(sample_2) < 0) && (counted_signal(sample_7) < 0)
        bits_noisy(iterator) = 0;
    else
        bits_noisy(iterator) = 1;
    end
    
    % move to next bit
    sample_2 = sample_2 + 10;
    sample_7 = sample_7 + 10;
end

% compute bit error rate
error = 0;
error = abs(bits_clean-bits_noisy);
bit_error_rate = sum(error)/total_bits;
    