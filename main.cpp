#include "GameManager.h"
#include "Menu.h"
#include "Exceptions.h"

int main() {
    try {
        GameManager game_manager;
        if (!game_manager.initialize()) {
            return 1;
        }

        std::vector<Team*> team_ptr;
        team_ptr.reserve(game_manager.get_teams().size());
        for (const auto& team : game_manager.get_teams()) {
            team_ptr.push_back(team.get());
        }

        try {
            Season season(team_ptr);
            const Player player(game_manager.get_my_team());
            const Menu menu(game_manager, const_cast<Player&>(player), season);
            menu.run();
        } catch (const RaceWeekendException& e) {
            std::cerr << "Race Weekend Error: " << e.what() << "\n";
            return 1;
        } catch (const InvalidTeamException& e) {
            std::cerr << "Team Error: " << e.what() << "\n";
            return 1;
        }

    } catch (const ConfigurationFileException& e) {
        std::cerr << "Configuration Error: " << e.what() << "\n";
        return 1;
    } catch (const Exceptions& e) {
        std::cerr << "Game Error: " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}