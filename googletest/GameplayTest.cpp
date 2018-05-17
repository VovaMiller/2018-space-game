#include <gtest/gtest.h>
#include <DiggerOffline/Game.h>
#include <DiggerOffline/Gameplay.h>
#include <fstream>
#include <stdio.h>

TEST(GameTest, Initialization) {
    Game* game;
    ASSERT_NO_THROW(game = Game::Instance());
    ASSERT_NE(game, nullptr);
    ASSERT_NE(game->get_settings(), nullptr) << "The settings had to be initialized.";
    ASSERT_GT(game->kGamedata.size(), 0) << "The game must have path to Gamedata.";
    ASSERT_GT(game->kGamemaps.size(), 0) << "The game must have path to Gamemaps.";
    ASSERT_NO_THROW(delete game) << "Something has gone wrong during the destruction of Game.";
}

TEST(GameplayTest, NewSaveLoad) {
    Gameplay* gameplay;
    std::string map_path;
    Point2DInt test_pos(-1024, -1024);
    
    // Initialization.
    ASSERT_NO_THROW(gameplay = new Gameplay());
    ASSERT_NE(gameplay, nullptr);
    
    // Create a new map (NewMap).
    EXPECT_EQ(gameplay->get_actor(), nullptr) << "The game hasn't been started => There must be no actor.";
    EXPECT_EQ(gameplay->get_active_map(), "") << "The game hasn't been started => There must be no active map.";
    ASSERT_NO_THROW(gameplay->NewMap()) << "Something has gone wrong while creating a new map.";
    ASSERT_NE(gameplay->get_actor(), nullptr) << "The game has been started => There must be the actor.";
    ASSERT_NE(gameplay->get_active_map(), "") << "The game has been started => There must be any active map.";
    
    // Manipulations on the actor.
    EXPECT_TRUE(gameplay->get_actor()->IsActor()) << "The actor must be the actor.";
    ASSERT_NO_THROW(gameplay->UpdateScreenPosition()) << "Something has gone wrong while updating the screen position.";
    EXPECT_TRUE(gameplay->IsOnScreen(gameplay->get_actor())) << "The actor must be on the screen (in the beginning).";
    ASSERT_NO_THROW(gameplay->get_actor()->set_pos(test_pos)) << "Something has gone wrong while moving the actor.";
    ASSERT_EQ(gameplay->get_actor()->get_pos(), test_pos) << "The actor didn't chane his position with set_pos(..).";
    ASSERT_NO_THROW(gameplay->UpdateScreenPosition()) << "Something has gone wrong while updating the screen position.";
    EXPECT_TRUE(gameplay->IsOnScreen(gameplay->get_actor())) << "The actor must be on the screen (after moving).";
    
    // Save & Halt
    ASSERT_NO_THROW(gameplay->SaveMap()) << "Something has gone wrong while saving the map.";
    map_path = gameplay->get_active_map();
    ASSERT_NO_THROW(gameplay->Halt()) << "Something has gone wrong while halting the map.";
    EXPECT_EQ(gameplay->get_actor(), nullptr) << "The game has been halted => There must be no actor.";
    EXPECT_EQ(gameplay->get_active_map(), "") << "The game has been halted => There must be no active map.";
    
    // Load
    std::ifstream ifs(map_path);
    ASSERT_FALSE(ifs.fail()) << "The map has been saved, but no related file has been found.";
    ifs.close();
    ASSERT_NO_THROW(gameplay->LoadMap(map_path)) << "Something has gone wrong while loading the map.";
    ASSERT_NE(gameplay->get_actor(), nullptr) << "The map has been loaded => There must be the actor.";
    ASSERT_NE(gameplay->get_active_map(), "") << "The map has been loaded => There must be any active map.";
    EXPECT_EQ(gameplay->get_actor()->get_pos(), test_pos) << "Actor's new positon hasn't been saved.";
    
    // Finalizing.
    ASSERT_NO_THROW(delete gameplay) << "Something has gone wrong during the destruction of Gameplay.";
    std::remove(map_path.c_str());
}
