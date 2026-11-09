export module priority_queue;

import std;
import heap;

export namespace graphs {
    template <typename Element, typename Comparator = std::less<>>
    class PriorityQueue {
    private:
        std::vector<Element> container;
        Comparator compare;

    public:
        PriorityQueue(const int size = 0, Comparator comparator = {}) {
            if (size > 0) {
                container.reserve(size);
            }
            compare = comparator;
        }

        explicit PriorityQueue(const std::vector<Element>& values, Comparator comparator = {}) {
            container = values;
            compare = comparator;

            std::span<Element> elements{container};
            graphs::build_heap(elements, compare);
        }

        auto size() const {
            return container.size();
        }

        void clear() {
            container.clear();
        }

        bool empty() const {
            return container.empty();
        }

        Element top() const {
            return container.front();
        }

        void push(Element value) {
            container.push_back(value);
            auto item_index = container.size() - 1;
            while (item_index > 0) {
                const auto parent_index = (item_index - 1) /2;

                // this is less or greater
                if (!compare(container[parent_index], container[item_index])) {
                    break;
                }
                //element is smaller/bigger than the parent element
                std::swap(container[parent_index], container[item_index]);
                item_index = parent_index;
            }
        }

        Element pop() {
            const Element value = container.front();
            if (container.size() == 1) {
                container.pop_back();
                return value;
            }

            container[0] = container.back();
            container.pop_back();

            graphs::heap_sift_down(std::span<Element>{container}, 0, compare);

            return value;
        }
    };
}
