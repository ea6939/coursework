alphabet = [1 2 3 4 5 6 7 8];
v_prob = ones(size(alphabet))/length(alphabet);

k = 10000; % length of sequence
n = length(alphabet); % range of sequence
sequence = randsample(n,k,true,v_prob);

number_of_symbol_i = zeros(size(alphabet));
prob_of_symbol_i = zeros(size(alphabet));

for i=1:length(sequence)
    for j=1:length(alphabet)
        if (sequence(i) == alphabet(j))
            number_of_symbol_i(j) = number_of_symbol_i(j) + 1;
        end
    end
end

for i=1:length(alphabet)
    prob_of_symbol_i(i) = number_of_symbol_i(i)/length(sequence);
end
