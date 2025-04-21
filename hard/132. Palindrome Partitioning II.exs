defmodule Solution do
  @spec min_cut(s :: String.t()) :: integer
  def min_cut(s) do
    n = String.length(s)
    chars = :array.from_list(String.to_charlist(s))
    cuts = :array.new(n, default: 0)

    # Inisialisasi max cut tiap posisi dengan nilai maksimal
    cuts =
      Enum.reduce(0..(n - 1), cuts, fn i, acc ->
        :array.set(i, i, acc)
      end)

    # Expand palindrome dari tengah (odd and even)
    cuts = Enum.reduce(0..(n - 1), cuts, fn center, acc ->
      acc
      |> expand(chars, n, center, center)     # odd length
      |> expand(chars, n, center, center + 1) # even length
    end)

    :array.get(n - 1, cuts)
  end

  defp expand(cuts, chars, n, left, right) do
    cond do
      left < 0 or right >= n ->
        cuts

      :array.get(left, chars) != :array.get(right, chars) ->
        cuts

      true ->
        new_cuts =
          if left == 0 do
            :array.set(right, 0, cuts)
          else
            min_cut = min(:array.get(right, cuts), :array.get(left - 1, cuts) + 1)
            :array.set(right, min_cut, cuts)
          end

        expand(new_cuts, chars, n, left - 1, right + 1)
    end
  end
end
