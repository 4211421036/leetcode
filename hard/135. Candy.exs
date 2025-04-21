defmodule Solution do
    def helper(ratings, acc, increment, previous, less_chain, greater_chain, add_chains) do
    case ratings do
      [h1, h2 | t] ->
        current =
          if h1 > h2 do
            :greater
          else
            if h1 < h2 do
              :less
            else
              :equal
            end
          end

        if current == previous || previous == :none do
          # don't need to continuing increase increment for chains of the same rating
          if current == :equal do
            helper([h2 | t], acc + increment, 1, current, 0, 0, false)
          else
            less_chain = if current == :less do less_chain + 1 else less_chain end
            greater_chain = if current == :greater do greater_chain + 1 else greater_chain end

            # each continous chain of :greater and :less results in higher increments
            helper([h2 | t], acc + increment, increment + 1, current, less_chain, greater_chain, add_chains)
          end
        else
          add_missing = if add_chains && greater_chain < less_chain do abs(greater_chain - less_chain) else 0 end

          # don't need to continuing increase increment for chains of the same rating
          if current == :equal do
            helper([h2 | t], acc + increment + add_missing, 1, current,0,0, false)
          else
            if current == :greater && previous == :less do
              # switch from less to greater results in deferring calculation of current number,
              # depends on how long the chains are
              helper([h2 | t], acc + 1, 2, current, less_chain, greater_chain+1, true)
            else
              # switch from greater to less or less to greater results in the next child getting 2 candies
              helper([h2 | t], acc + increment + add_missing, 2, current, 1, 0, false)
            end
          end
        end
      [_] ->
        add_missing = if add_chains && greater_chain < less_chain do abs(greater_chain - less_chain) else 0 end
        acc + increment + add_missing
    end
  end

  @spec candy(ratings :: [integer]) :: integer
  def candy(ratings) do
    helper(ratings, 0, 1, :none, 0, 0, false)
  end
end
