#pragma once

#include <array>
#include <cstddef>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

namespace aA {

	struct Match {
		std::size_t pattern_index;   // which word
		std::size_t end_pos;         // index of its last character
	};

	//brute force
	class NaiveMatcher {
	public:
		explicit NaiveMatcher(std::vector<std::string> patterns)
			: patterns_(std::move(patterns)) {}

		std::vector<Match> scan(std::string_view text) const {
			std::vector<Match> out;

			for (std::size_t i = 0; i < patterns_.size(); ++i) {
				const std::string& pattern = patterns_.at(i);
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
		std::vector<std::string> patterns_;
	};

	
	class AhoCorasick {
	public:
		explicit AhoCorasick(std::vector<std::string> patterns)
			: patterns_(std::move(patterns)) {
			nodes_.push_back(Node{});               // node 0 is at the root

			for (std::size_t i = 0; i < patterns_.size(); i++) {
				insert(patterns_.at(i), i);
			}
		}

		std::size_t node_count() const { return nodes_.size(); }

		// temporary -- prints the trie 
		void trie() const {
			for (std::size_t n = 0; n < nodes_.size(); n++) {
				std::cout << "node " << n;

				if (!nodes_.at(n).ends.empty()) {
					std::cout << "  * ends:";
					for (std::size_t w : nodes_.at(n).ends) {
						std::cout << " " << patterns_.at(w);
					}
				}
				std::cout << "\n";

				for (int c = 0; c < 256; c++) {
					const int child = nodes_.at(n).next.at(static_cast<std::size_t>(c));
					if (child != -1) {
						std::cout << "    '" << char(c) << "' -> node " << child << "\n";
					}
				}
			}
		}

	private:
		struct Node {
			std::array<int, 256> next{};        // next[c] = child index, -1 = none
			std::vector<std::size_t> ends;      // words ending at this node
			Node() { next.fill(-1); }
		};

		void insert(const std::string& word, std::size_t index) {
			if (word.empty()) return;

			int current = 0;                     // start at the root
			for (const char ch : word) {
				const auto c = static_cast<unsigned char>(ch);

				if (nodes_.at(static_cast<std::size_t>(current)).next.at(c) == -1) {
					nodes_.push_back(Node{});    // no edge yet, create a node
					nodes_.at(static_cast<std::size_t>(current)).next.at(c) =
						static_cast<int>(nodes_.size() - 1);
				}

				current = nodes_.at(static_cast<std::size_t>(current)).next.at(c);
			}

			nodes_.at(static_cast<std::size_t>(current)).ends.push_back(index);
		}

		std::vector<std::string> patterns_;
		std::vector<Node> nodes_;
	};

} 