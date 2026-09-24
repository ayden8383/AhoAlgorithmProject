#pragma once

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>
#include <array>
#include <iostream>

namespace aA {
	struct Match {
		std::size_t pattern_index;
		std::size_t end_pos;
	};

	class NaiveMatcher {
	public:
		explicit NaiveMatcher(std::vector<std::string> patterns)
			: patterns(std::move(patterns)) {}

		std::vector<Match> scan(std::string_view text) const {
			std::vector<Match> out;

			 for (std::size_t i = 0; i < patterns.size(); ++i) {
				const std::string& pattern = patterns.at(i);
				if (pattern.empty()) continue;

				std::size_t from = 0;
				while (true) {
					const std::size_t start = text.find(pattern, from);
					if (start == std::string_view::npos) break;

					out.push_back(Match{ i, start + pattern.size() - 1 });
					from = start + 1;
				}
			}

			 return out;
		}

	private:
		std::vector<std::string> patterns;
	};

	class AhoCorasick {
	public:
		explicit AhoCorasick(std::vector<std::string> patterns)
			:patterns(std::move(patterns)) {
			nodes.push_back(Node{});
			for (std::size_t i = 0; i < patterns.size(); i++) {
				insert(patterns.at(i), i);
			}
		}

	private:
		struct Node {
			std::array<int, 256> next{};
			std::vector<std::size_t> ends;
			Node() { next.fill(-1); }
		};

		std::vector<std::string> patterns;
		std::vector<Node> nodes;
	};
}