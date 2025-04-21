defmodule Solution do
  @spec find_min(nums :: [integer]) :: integer
  def find_min(nums) do
    # Start binary search with full array range
    find_min_helper(nums, 0, length(nums) - 1)
  end

  defp find_min_helper(nums, low, high) do
    # Base case: when search range has one element
    if low >= high do
      Enum.at(nums, low)
    else
      mid = div(low + high, 2)
      
      cond do
        # Minimum must be in right half
        Enum.at(nums, mid) > Enum.at(nums, high) ->
          find_min_helper(nums, mid + 1, high)
        
        # Minimum is in left half (including mid)
        Enum.at(nums, mid) < Enum.at(nums, high) ->
          find_min_helper(nums, low, mid)
        
        # Handle duplicates by reducing search range
        true ->
          find_min_helper(nums, low, high - 1)
      end
    end
  end
end
