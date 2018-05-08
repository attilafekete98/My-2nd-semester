/**
 * @brief FUTURE DEBRECEN, UDProg1/DeacH Lightsaber
 *
 * @file fenykard.cpp
 * @author  Norbert Bátfai <nbatfai@gmail.com>
 * @version f9f2ls.0.0.14
 *
 * @section LICENSE
 *
 * Copyright (C) 2018 Norbert Bátfai, batfai.norbert@inf.unideb.hu, PhD
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 * This program supports an alternative grading scale for the
 * course "High level programming language I" and the DEAC esport department.
 *
 * $ g++ -I/home/batfai/boost66/include/ -L/home/batfai/boost66/lib/ player.hpp fenykard.cpp -o fenykard -lboost_system -lboost_filesystem -lboost_program_options -lboost_date_time -std=c++14
 *
 * UDPROG Előadás jegymegajánlás alappontok:
 * $ ./fenykard --roots City/Debrecen/Oktatás/Informatika/Programozás/DEIK/Prog1/Példák/Előadás City/Debrecen/Szórakozás/Könyv/Ismeretterjesztő/Informatika City/Debrecen/Oktatás/Informatika/Programozás/Tankönyv\ olvasás City/Debrecen/Oktatás/Informatika/Programozás/UDPROG City/Debrecen/Szórakozás/Előadás/Ismeretterjesztő/Informatika City/Debrecen/Oktatás/Informatika/Programozás/Forráskód\ olvasás City/Debrecen/Oktatás/Informatika/Programozás/Forráskód\ írás City/Debrecen/Oktatás/Informatika/Programozás/API\ doksi\ olvasás City/Debrecen/Oktatás/Informatika/Programozás/DEIK/Prog1/Labor/Védés City/Debrecen/Szórakozás/Film -v
 *
 * UDPROG Előadás jegymegajánlás tradicionális rangsor:
 * $ ./fenykard --roots City/Debrecen/Oktatás/Informatika/Programozás/DEIK/Prog1/Példák/Előadás City/Debrecen/Szórakozás/Könyv/Ismeretterjesztő/Informatika City/Debrecen/Oktatás/Informatika/Programozás/Tankönyv\ olvasás City/Debrecen/Oktatás/Informatika/Programozás/UDPROG City/Debrecen/Szórakozás/Előadás/Ismeretterjesztő/Informatika City/Debrecen/Oktatás/Informatika/Programozás/Forráskód\ olvasás City/Debrecen/Oktatás/Informatika/Programozás/Forráskód\ írás City/Debrecen/Oktatás/Informatika/Programozás/API\ doksi\ olvasás City/Debrecen/Oktatás/Informatika/Programozás/DEIK/Prog1/Labor/Védés City/Debrecen/Szórakozás/Film -v --db=db-2018-03-10.csv
 *
 * UDPROG Labor érdemjegy
 *
 * $ ./fenykard --trad-lab-mark --roots City/Debrecen/Oktatás/Informatika/Programozás/DEIK/Prog1/Labor/Védés/I City/Debrecen/Oktatás/Informatika/Programozás/DEIK/Prog1/Labor/Védés/II City/Debrecen/Oktatás/Informatika/Programozás/DEIK/Prog1/Labor/Védés/III -v --db=db-2018-03-10.csv
 *
 * UDPROG Labor jegymegajánlás alappontok:
 * $ ./fenykard -r City/Debrecen/Oktatás/Informatika/Programozás/DEIK/Prog1/Példák/Labor -v
 *
 * UDPROG Labor jegymegajánlás tradicionális rangsor:
 * $ ./fenykard -r City/Debrecen/Oktatás/Informatika/Programozás/DEIK/Prog1/Példák/Labor -v --db=db-2018-03-10.csv
 *
 * DEAC pontok:
 * $ ./fenykard -r City/Debrecen/Sport/Esport/DEAC-Hackers -v
 *
 * DEAC teadicionális rangsor:
 * $ ./fenykard -r City/Debrecen/Sport/Esport/DEAC-Hackers -v --db=db-2018-03-10.csv
 *
 */

#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "player.hpp"

int get_points ( boost::filesystem::path file )
{
        int points {0};

        boost::filesystem::ifstream ifs {file};

        std::string line;

        while ( std::getline ( ifs, line ) ) {

                int r = line.find_last_of ( "0123456789" );
                int l = line.find_last_not_of ( "0123456789", r );

                std::string val = line.substr ( l, r );

                try {
		  
                        points += std::stoi ( val );
			
                } catch (std::invalid_argument e) {

		  std::cerr << line << std::endl;
		  std::cerr << val << std::endl;		  
		  throw e;
		  
                }
        }

        return points;
}

int sum_points ( std::map<std::string, int> &acts )
{
        int sum = std::accumulate ( acts.begin(), acts.end(), 0,
        [] ( int total, std::pair<std::string, int> pair ) {
                return total + pair.second;
        } );

        return sum;
}

void print_acts ( std::map <std::string, int> acts )
{
        std::cout << "Total score: " << sum_points ( acts ) << std::endl;

        for ( auto & a : acts )
                std::cout << std::setw ( 4 ) << a.second << "    " << a.first << std::endl;

}

void read_acts ( boost::filesystem::path path, std::map <std::string, int> &acts )
{

        if ( is_regular_file ( path ) ) {

                std::string ext ( ".props" );
                if ( !ext.compare ( boost::filesystem::extension ( path ) ) ) {

                        std::string actpropspath = path.string();
                        std::size_t end = actpropspath.find_last_of ( "/" );
                        std::string act = actpropspath.substr ( 0, end );

                        acts[act] = get_points ( path );

                }

        } else if ( is_directory ( path ) )
                for ( boost::filesystem::directory_entry & entry : boost::filesystem::directory_iterator ( path ) )
                        read_acts ( entry.path(), acts );

}

std::map <std::string, int> acts_map ( std::vector<std::string>  folder_names )
{
        std::map <std::string, int> acts;

        for ( const auto & node : folder_names ) {

                boost::filesystem::path root ( node );
                read_acts ( root, acts );

        }

        return acts;

}

std::map <std::string, int> trad_map ( std::string db_name, std::map <std::string, int> &act_points )
{

        std::map <std::string, int> rank;

        std::ifstream db ( db_name );

        std::string line;
        while ( std::getline ( db, line ) ) {

                boost::tokenizer<boost::escaped_list_separator<char>> tokens {line};

                auto iter = tokens.begin();
                std::string name = *iter;
                std::string act = *++iter;
                act = act.substr ( 2 );

                rank[name] += act_points[act];

        }

        return rank;
}

std::vector<std::pair<std::string, int>> sort_map ( std::map <std::string, int> &rank )
{
        std::vector<std::pair<std::string, int>> ordered;

        for ( auto & i : rank ) {
                if ( i.second ) {
                        std::pair<std::string, int> p {i.first, i.second};
                        ordered.push_back ( p );
                }
        }

        std::sort (
                std::begin ( ordered ), std::end ( ordered ),
        [ = ] ( auto && p1, auto && p2 ) {
                return p1.second > p2.second;
        }
        );

        return ordered;
}

void trad_grading_scale ( std::string db_name, std::map <std::string, int> &act_points )
{
        std::map <std::string, int> rank = trad_map ( db_name, act_points );
        // See also https://www.twitch.tv/videos/232384581 that introduces the difference between the traditional grading scale and an alternative one

        std::vector<std::pair<std::string, int>> res = sort_map ( rank );

        for ( auto & i : res )
                std::cout << i.first << " "  << i.second << std::endl;
}

std::ostream &print_gource_inp ( std::string db_name, std::ostream &os )
{

        std::map <std::string, int> act_counter;

        std::ifstream db ( db_name );

        std::string line;
        while ( std::getline ( db, line ) ) {

                boost::tokenizer<boost::escaped_list_separator<char>> tokens {line};

                auto iter = tokens.begin();
                std::string name = *iter;
                std::string act = *++iter;
                std::string tstamp = *++iter;

                act = act.substr ( 2 );

                // tstamp to Unix epoch time concersion
                boost::posix_time::ptime ts ( boost::posix_time::time_from_string ( tstamp ) );
                struct tm stm = boost::posix_time::to_tm ( ts );
                time_t epoch = std::mktime ( &stm );

                ++act_counter[act];

                os << epoch << "|" << name << "|";
                if ( act_counter[act] == 1 )
                        os << "A"  << "|";
                else
                        os << "M"  << "|";
                os << act << std::endl;

        }

        return os;
}


using P_act_per_day = std::map< std::string, std::map< int, std::map< std::string, double > > >;
// the probabilites of acts on any given day of the week
// act_per_day["user"][ day of a week ]["act"] = number of occurrences

P_act_per_day act_probs ( std::string db_name )
{

        P_act_per_day act_per_day;

        std::ifstream db ( db_name );

        bool first {true};
        boost::gregorian::date firstDate;
        boost::posix_time::ptime ts;
        std::string line;
        while ( std::getline ( db, line ) ) {

                boost::tokenizer<boost::escaped_list_separator<char>> tokens {line};

                auto iter = tokens.begin();
                std::string name = *iter;
                std::string act = *++iter;
                std::string tstamp = *++iter;

                act = act.substr ( 2 );

                //boost::posix_time::ptime ts ( boost::posix_time::time_from_string ( tstamp ) );
                ts = boost::posix_time::time_from_string ( tstamp );
                if ( first ) {
                        firstDate = ts.date();
                        first = false;
                }

                struct tm stm = boost::posix_time::to_tm ( ts );

                ++act_per_day[name][stm.tm_wday][act];

        }

        boost::gregorian::date lastDate = ts.date();
        boost::gregorian::date_duration dd = lastDate - firstDate;
        long days = dd.days();

        if ( days < 1 )
                days = 1;

        std::cout << "days = " << days << std::endl;

        for ( auto & user : act_per_day ) {
                for ( auto & day : user.second ) {
                        for ( auto & act : day.second ) {

                                if ( act.second > days )
                                        act.second = days;

                                act.second /= days;

                        }
                }
        }

        return act_per_day;
}

P_act_per_day nact_probs ( P_act_per_day  act_per_day )
{

        P_nact_per_day act_counter;

        for ( auto & user : act_per_day ) {
                for ( auto & day : user.second ) {
                        for ( auto & act : day.second ) {

                                ++act_counter[day.first][act.first];

                        }
                }

        }

        for ( auto & user : act_per_day ) {
                for ( auto & day : user.second ) {
                        for ( auto & act : day.second ) {

                                act_per_day[user.first][day.first][act.first] /= act_counter[day.first][act.first];

                        }
                }

        }

        return act_per_day;
}


void print_act_probs ( P_act_per_day & act_per_day )
{
        for ( auto & user : act_per_day ) {
                for ( auto & day : user.second ) {
                        for ( auto & act : day.second ) {

                                std::cout << user.first << " " << day.first <<  " " << act.first << " " << act.second << std::endl;

                        }
                }

        }
}

using Submarks = std::map< std::string, std::map< std::string, int > >;
// act_per_day["user"][ "vedes?" ] = jegy

void print_marks ( Submarks & submarks )
{
        for ( auto & user : submarks ) {


                int sum = std::accumulate ( user.second.begin(), user.second.end(), 0,
                [] ( int total, std::pair<std::string, int> pair ) {
                        return total + pair.second;
                } );


                std::cout << user.first << " #" << user.second.size() << " mark: " << sum / user.second.size() << std::endl;

        }
}

void print_submarks ( Submarks & submarks )
{
        for ( auto & user : submarks ) {
                for ( auto & root : user.second ) {

                        std::cout << user.first << " "  << root.first << " " << root.second << std::endl;

                }

        }
}

bool repl_mark ( Submarks & submarks, std::string name, std::string act, std::string root, std::string marks, int markv )
{
        bool replaced {false};

        if ( !act.find ( root ) ) {

                auto i = act.find ( marks );

                if ( i != std::string::npos ) {

                        if ( submarks[name].find ( root ) != submarks[name].end() ) {

                                if ( submarks[name][root] < markv ) {
                                        submarks[name][root] = markv;
                                        replaced = true;
                                }

                        } else {

                                submarks[name][root] = markv;
                                replaced = true;

                        }

                }

        }

        return replaced;
}

Submarks get_submarks ( std::vector<std::string> folder_names, std::string db_name )
{

        Submarks submarks;

        std::ifstream db ( db_name );

        std::string line;
        while ( std::getline ( db, line ) ) {

                boost::tokenizer<boost::escaped_list_separator<char>> tokens {line};

                auto iter = tokens.begin();
                std::string name = *iter;
                std::string act = *++iter;
                std::string tstamp = *++iter;

                act = act.substr ( 2 );

                for ( const auto & node : folder_names ) {

                        if ( repl_mark ( submarks, name, act, node, "jeles", 5 ) )
                                ;
                        else if ( repl_mark ( submarks, name, act, node, "jó", 4 ) )
                                ;
                        else if ( repl_mark ( submarks, name, act, node, "közepes", 3 ) )
                                ;
                        else if ( repl_mark ( submarks, name, act, node, "elégséges", 2 ) )
                                ;
                        else if ( repl_mark ( submarks, name, act, node, "elégtelen", 1 ) )
                                ;
                }

        }

        return submarks;
}

std::map <std::string, int> get_marks ( Submarks & submarks )
{

        std::map <std::string, int> marks;

        for ( auto & user : submarks ) {


                int sum = std::accumulate ( user.second.begin(), user.second.end(), 0,
                [] ( int total, std::pair<std::string, int> pair ) {
                        return total + pair.second;
                } );

                marks[user.first] = sum / user.second.size();

        }

        return marks;

}

struct tm *next_calendar_day ( struct tm *date )
{

        struct tm *real_date;

        ++date->tm_mday;

        time_t realepoch = std::mktime ( date );
        real_date = std::gmtime ( &realepoch );
        *date = *real_date;

        return date;
}

int main ( int argc, char *argv[] )
{
        // If you use this sample you should add your copyright information here too:
        /*
        std::cout << "This Prog1 Lightsaber has been modified by <Your Name>" << std::endl
        << "Copyright (C) 2018 Norbert Bátfai" << std::endl
        << "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>" << std::endl
        */

        // Do not remove this copyright notice!
        std::cout << "FUTURE DEBRECEN, UDProg1/DeacH Lightsaber to support alternative grading scales" << std::endl
                  << "Copyright (C) 2018 Norbert Bátfai" << std::endl
                  << "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>" << std::endl
                  << "This is free software: you are free to change and redistribute it." << std::endl
                  << "There is NO WARRANTY, to the extent permitted by law." << std::endl;

        std::string def_ops_simout = "simul-out.csv";
        std::vector<std::string> def_ops_roots = {
                "City/Debrecen/Oktatás/Informatika/Programozás/DEIK/Prog1/Példák/Előadás",
                "City/Debrecen/Szórakozás/Könyv/Ismeretterjesztő/Informatika",
                "City/Debrecen/Oktatás/Informatika/Programozás/Tankönyv olvasás"
        };
        std::string def_ops_breakday = "2019-04-10";

        boost::program_options::options_description desc ( "Options" );
        desc.add_options()
        ( "version", "print version number" )
        ( "help", "print help message" )
        ( "verbose,v", boost::program_options::value< bool > ()->default_value ( false )->implicit_value ( true ),
          "Verbose mode." )
        ( "roots,r", boost::program_options::value< std::vector<std::string> >(),
          "the name of a subdirectories of the FUTURE activity trees to be processed by this program." )
        ( "db", boost::program_options::value< std::string > (),
          "the name of a  database dump CSV file. There is no default value for this option." )
        ( "gource", boost::program_options::value< bool > ()->default_value ( false )->implicit_value ( true ),
          "prints out users and activities in Gource input format." )
        ( "trad-lab-mark", boost::program_options::value< bool > ()->default_value ( false )->implicit_value ( true ),
          "compute and print out labour mark." )
        ( "trad-grading-scale", boost::program_options::value< bool > ()->default_value ( true )->implicit_value ( true ),
          "generates and prints out the traditional grading scale." )
        ( "probs", boost::program_options::value< bool > ()->default_value ( false )->implicit_value ( true ),
          " indicates that the program will generate probabilities for activities." )
        ( "simul", boost::program_options::value< bool > ()->default_value ( false )->implicit_value ( true ),
          "indicates that the program will simulate users' acts." )
        ( "simout", boost::program_options::value< std::string > ()->default_value ( def_ops_simout ),
          "the name of an output CSV file that contains the simulated activities to be generated by this program. The structure of this out file and the input file (appeared in db option) are the same." )
        ( "break-day", boost::program_options::value< std::string > ()->default_value ( def_ops_breakday ),
          "a date in format year year-month-day (eg 2018-04-10) when simulation will end." )
        ;

        boost::program_options::positional_options_description pdesc;
        pdesc.add ( "roots", -1 );

        boost::program_options::variables_map vm;
        boost::program_options::store ( boost::program_options::command_line_parser ( argc, argv ).options ( desc ).positional ( pdesc ).run(), vm );
        boost::program_options::notify ( vm );

        bool verbose {false};

        if ( vm.count ( "verbose" ) )
                if ( vm["verbose"].as<bool>() )
                        verbose = true;

        if ( vm.count ( "version" ) ) {
                std::cout << "FUTURE DEBRECEN, UDProg1/DeacH Lightsaber, f9f2ls.0.0.9" << std::endl;
                return 0;
        } else if ( vm.count ( "help" ) ) {
                std::cout << "This program supports alternative grading scales for the course \"High level programming language I\" and the DEAC esport department." << std::endl;
                std::cout << desc << std::endl;
                std::cout << "Please report bugs to: nbatfai@gmail.com" << std::endl;
                return 0;
        }

        if ( vm.count ( "roots" ) )
                def_ops_roots = vm["roots"].as < std::vector<std::string >> ();

        std::map <std::string, int> act_points = acts_map ( def_ops_roots );

        if ( verbose ) {

                std::cout << "\nActivities (points activity)\n" << std::endl;
                print_acts ( act_points );

        }

        if ( vm.count ( "db" ) ) {

                if ( vm.count ( "trad-lab-mark" ) ) {
                        if ( vm["trad-lab-mark"].as<bool>() ) {

                                if ( verbose )
                                        std::cout << "\nTraditional labour mark\n" << std::endl;

                                Submarks submarks = get_submarks ( def_ops_roots, vm["db"].as < std::string > () );

                                if ( verbose )
                                        print_submarks ( submarks );

                                print_marks ( submarks );

                                std::map <std::string, int> marks = get_marks ( submarks );

                                std::vector<std::pair<std::string, int>> res = sort_map ( marks );

                                for ( auto & i : res )
                                        std::cout << i.first << " "  << i.second << std::endl;

                                return 0;
                        }
                }

                if ( vm.count ( "gource" ) ) {
                        if ( vm["gource"].as<bool>() ) {

                                if ( verbose )
                                        std::cout << "\nInput for Gource\n" << std::endl;

                                print_gource_inp ( vm["db"].as < std::string > (), std::cout );

                        }
                }

                if ( vm.count ( "trad-grading-scale" ) ) {
                        if ( vm["trad-grading-scale"].as<bool>() ) {

                                if ( verbose )
                                        std::cout << "\nTraditional grading scale\n" << std::endl;

                                trad_grading_scale ( vm["db"].as < std::string > (), act_points );
                        }
                }

                if ( vm.count ( "probs" ) || vm.count ( "simul" ) ) {
                        if ( vm["probs"].as<bool>() || vm["simul"].as<bool>() ) {

                                boost::gregorian::date break_day = boost::gregorian::from_string ( vm["break-day"].as < std::string > () );

                                if ( verbose )
                                        std::cout << "\nThe probabilites of acts\n" << std::endl;

                                P_act_per_day act_per_day = act_probs ( vm["db"].as < std::string > () );

                                if ( verbose )
                                        print_act_probs ( act_per_day );

                                if ( vm.count ( "simul" ) ) {

                                        if ( vm["simul"].as<bool>() ) {


                                                P_act_per_day nact_per_day = nact_probs ( act_per_day );

                                                if ( verbose ) {
                                                        std::cout << "\nThe normalized probabilites of acts\n" << std::endl;
                                                        print_act_probs ( nact_per_day );

                                                        std::cout << "\nThe simulation of acts\n" << std::endl;

                                                }

                                                std::default_random_engine rnd;
                                                rnd.seed ( std::random_device {}() );

                                                std::vector<Player> users;
                                                users.reserve ( nact_per_day.size() );

                                                for ( auto & user : nact_per_day ) {

                                                        users.push_back ( Player {rnd, user.first, user.second} );

                                                }

                                                struct tm date;
                                                struct tm *tmpdate;
                                                time_t now = std::time ( NULL );
                                                tmpdate = std::gmtime ( &now );
                                                date = *tmpdate;

                                                std::fstream csv_out ( vm["simout"].as < std::string > (), std::ios_base::out );

                                                do {

                                                        boost::gregorian::date n = boost::gregorian::date_from_tm ( date );

                                                        if ( n.year() == break_day.year()
                                                                        && n.month() == break_day.month()
                                                                        && n.day() == break_day.day() )
                                                                break;

                                                        if ( verbose )
                                                                std::cout << std::asctime ( &date ) << std::endl;


                                                        for ( auto & user : users ) {

                                                                user.devel ( date.tm_wday, n, csv_out );

                                                        }


                                                } while ( next_calendar_day ( &date )->tm_year < 2019+100 - 1900 );

                                        }
                                }

                        }

                }

        }

}
