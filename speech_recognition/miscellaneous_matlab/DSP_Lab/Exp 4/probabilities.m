function prob_of_level_m = probabilities(Y,number_of_levels)

size_size = size(Y);
size_size(2) = ceil(size_size(2)/32);
Q = zeros(size_size);

prob_of_level_m = zeros([size_size(1) number_of_levels]);

for n = 1:size_size(1)
    % normalize each row so that the values are between 0 and 1
    scale_factor = max(Y(n,:));
    Y(n,:) = Y(n,:)/scale_factor;
   
    % quantize
    for iterator = 1:length(Y(n,:))
        
        % if the signal value is very small
        lowest_level = (2/number_of_levels) - 1;
        if (Y(n,iterator) < lowest_level)
            prob_of_level_m(n,1) = prob_of_level_m(n,1) + 1;
            
        else
            % middle case: if the signal value is in one of the intermediate
            % levels
            for i = 1:number_of_levels
                level = (i*2/number_of_levels) - 1;
         
                if ((Y(n,iterator) > level) && (Y(n,iterator) < level+2/number_of_levels))
                    prob_of_level_m(n,i) = prob_of_level_m(n,i) + 1;
                    
                elseif((Y(n,iterator) > level))
                    prob_of_level_m(n,i+1) = prob_of_level_m(n,i+1) + 1;
                    
                end
            end
        end
    end
    
    Q(n,:) = Q(n,:)*scale_factor;
end
end