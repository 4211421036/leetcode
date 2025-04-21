defmodule Solution do
  @spec max_points(points :: [[integer]]) :: integer
  def max_points(points) do
    n = length(points)
    
    if n <= 2 do
      n
    else
      0..n-2
      |> Enum.reduce(2, fn i, max_count ->
        i+1..n-1
        |> Enum.reduce(max_count, fn j, current_max ->
          [x1, y1] = Enum.at(points, i)
          [x2, y2] = Enum.at(points, j)
          
          count = 2 + 
            Enum.count(0..n-1, fn k -> 
              k != i && k != j && 
              collinear(x1, y1, x2, y2, Enum.at(points, k))
            end)
          
          max(current_max, count)
        end)
      end)
    end
  end
  
  defp collinear(x1, y1, x2, y2, [x3, y3]) do
    (y2 - y1) * (x3 - x1) == (y3 - y1) * (x2 - x1)
  end
end
