#include <bits/stdc++.h>
#include <cpp_elasticsearch/client.h>

void log(const std::string& indexName, const std::string& timestamp, const std::string& message, const std::string& level, const std::string& source) {
    cpp_elasticsearch::client esClient("http://localhost:9200");

    try {
        cpp_elasticsearch::document document;
        document["timestamp"] = timestamp;
        document["message"] = message;
        document["level"] = level;
        document["source"] = source;

        esClient.index(indexName, document);
        std::cout << "Data logged successfully to Elasticsearch!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Failed to log data to Elasticsearch: " << e.what() << std::endl;
    }
}

