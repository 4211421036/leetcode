defmodule Solution do
  @spec word_break(s :: String.t, word_dict :: [String.t]) :: [String.t]
  def word_break(s, word_dict) do
    word_set = MapSet.new(word_dict)
    max_len = word_dict |> Enum.map(&String.length/1) |> Enum.max()
    memo = %{}
    {result, _} = helper(s, word_set, max_len, memo)
    result
  end

  defp helper("", _word_set, _max_len, memo) do
    {[""], memo}
  end

  defp helper(s, word_set, max_len, memo) do
    case Map.get(memo, s) do
      nil ->
        max_len_to_check = min(max_len, String.length(s))
        result =
          for i <- 1..max_len_to_check,
              word = String.slice(s, 0, i),
              MapSet.member?(word_set, word) do
            {sub_sentences, new_memo} = helper(String.slice(s, i..-1), word_set, max_len, memo)
            for sentence <- sub_sentences do
              if sentence == "" do
                word
              else
                "#{word} #{sentence}"
              end
            end
          end
          |> List.flatten()

        memo = Map.put(memo, s, result)
        {result, memo}
      cached_result ->
        {cached_result, memo}
    end
  end
end
