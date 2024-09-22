#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp> // Include the JSON library
#include <algorithm>

// Location Class to represent a location
class Location {
public:
    std::string name;
    double latitude;
    double longitude;

    Location(std::string name, double latitude, double longitude) 
        : name(name), latitude(latitude), longitude(longitude) {}

    void display() {
        std::cout << "Location: " << name 
                  << ", Latitude: " << latitude 
                  << ", Longitude: " << longitude << std::endl;
    }
};

// Location Manager Class to handle adding, removing, and listing locations
class LocationManager {
private:
    std::vector<Location> locations;

public:
    void addLocation(const std::string& name, double lat, double lon) {
        locations.push_back(Location(name, lat, lon));
    }

    void removeLocation(const std::string& name) {
        locations.erase(std::remove_if(locations.begin(), locations.end(),
                        [&](Location& loc) { return loc.name == name; }), 
                        locations.end());
    }

    void listLocations() {
        for (const auto& loc : locations) {
            loc.display();
        }
    }
};

// WeatherVariable Class to represent different weather metrics (e.g., temperature, wind speed)
class WeatherVariable {
public:
    std::string name;
    double value;

    WeatherVariable(const std::string& name, double value) 
        : name(name), value(value) {}

    void display() {
        std::cout << "Weather Variable: " << name << " = " << value << std::endl;
    }
};

// WeatherVariableManager Class to manage a list of Weather Variables
class WeatherVariableManager {
private:
    std::vector<WeatherVariable> weatherVariables;

public:
    void addWeatherVariable(const std::string& name, double value) {
        weatherVariables.push_back(WeatherVariable(name, value));
    }

    void listWeatherVariables() {
        for (const auto& var : weatherVariables) {
            var.display();
        }
    }

    std::vector<WeatherVariable> getWeatherVariables() {
        return weatherVariables;
    }
};

class HistoricalWeatherSystem {
public:
    // Placeholder for fetching data from an API
    void fetchHistoricalWeather(const std::string& location) {
        std::cout << "Fetching historical weather data for " << location << "..." << std::endl;
    }

    void displayHistoricalWeather() {
        std::cout << "Displaying historical weather data..." << std::endl;
    }
};

class WeatherForecastingSystem {
public:
    // Placeholder for fetching weather forecast data from an API
    void fetchWeatherForecast(const std::string& location) {
        std::cout << "Fetching weather forecast for " << location << "..." << std::endl;
    }

    void displayWeatherForecast() {
        // Placeholder for displaying the fetched forecast data
        std::cout << "Displaying weather forecast..." << std::endl;
    }
};

class DataExporter {
public:
    // Export weather variables to CSV file
    void exportToCSV(const std::string& filename, const std::vector<WeatherVariable>& variables) {
        std::ofstream file(filename);
        file << "Variable,Value\n"; 
        for (const auto& var : variables) {
            file << var.name << "," << var.value << "\n"; 
        }
        file.close();
        std::cout << "Data exported to " << filename << std::endl;
    }

    // Export weather variables to JSON file
    void exportToJSON(const std::string& filename, const std::vector<WeatherVariable>& variables) {
        nlohmann::json jsonObj; 
        for (const auto& var : variables) {
            jsonObj[var.name] = var.value; 
        }
        std::ofstream file(filename);
        file << jsonObj.dump(4); 
        file.close();
        std::cout << "Data exported to " << filename << std::endl;
    }
};

int main() {
    // Location Management
    LocationManager locManager;
    locManager.addLocation("New York", 40.7128, -74.0060);
    locManager.addLocation("Los Angeles", 34.0522, -118.2437);
    locManager.listLocations(); // Display locations

    // Weather Variables Management
    WeatherVariableManager weatherVarManager;
    weatherVarManager.addWeatherVariable("Temperature", 23.5);
    weatherVarManager.addWeatherVariable("Wind Speed", 15.2);
    weatherVarManager.listWeatherVariables(); 

    // Fetch and Display Historical Weather Data 
    HistoricalWeatherSystem histWeather;
    histWeather.fetchHistoricalWeather("New York");
    histWeather.displayHistoricalWeather(); 

    // Fetch and Display Weather Forecast Data
    WeatherForecastingSystem weatherForecast;
    weatherForecast.fetchWeatherForecast("Los Angeles");
    weatherForecast.displayWeatherForecast(); 

    // Export Data to CSV and JSON
    DataExporter exporter;
    exporter.exportToCSV("weather_data.csv", weatherVarManager.getWeatherVariables());
    exporter.exportToJSON("weather_data.json", weatherVarManager.getWeatherVariables());

    return 0;
}
