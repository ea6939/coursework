% clear;
% 
% test = sin(1:100);
% 
% num_levels = 16;
% Q = quantizer_bank(test,num_levels);

G = Q(3,:);
num_levels = 32;
scale_factor = max(G);

prob_level_m = zeros([1,num_levels]);
sum_level_m = zeros([1,num_levels]);
value_of_level_m = zeros([1,num_levels]);

for m = 1:num_levels
   value_of_level_m(m) = scale_factor * ((m*2/num_levels) - 1);
end

for q = 1:num_levels
   for r = 1:length(G)
       if (threshold(G(r),value_of_level_m(q)) == 1)
           sum_level_m(q) = sum_level_m(q) + 1;
       end
   end
   prob_level_m(q) =  sum_level_m(q) / length(G);
end

entropy = 0;
sum_plogp = 0;
plogp = 0;

for i = 1:num_levels
    if (prob_level_m(i) ~= 0)
    plogp = -prob_level_m(i) * log2(prob_level_m(i));
    sum_plogp = sum_plogp + plogp;
    end
end

entropy = sum_plogp;
