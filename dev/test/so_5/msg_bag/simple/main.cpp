/*
 * A simple test for msg_bag.
 */

#include <so_5/all.hpp>

#include <various_helpers_1/time_limited_execution.hpp>

#include "../bag_params.hpp"

using namespace std;

int
main()
{
	try
	{
		run_with_time_limit(
			[]()
			{
				so_5::wrapped_env_t env;

				auto params = build_bag_params();

				for( const auto & p : params )
				{
					cout << "=== " << p.first << " ===" << endl;

					auto bag = env.environment().create_msg_bag( p.second );

					so_5::send< int >( bag->as_mbox(), 42 );

					auto r = so_5::receive(
							bag,
							so_5::rt::msg_bag::clock::duration::zero(),
							so_5::handler( []( int i ) {
								if( 42 != i )
									throw runtime_error( "unexpected int-message: "
											+ to_string( i ) );
							} ),
							so_5::handler( []( const std::string & s ) {
								throw runtime_error( "unexpected string msg: " + s );
							} ) );

					if( r != 1 )
						throw runtime_error( "unexpected value of so_5::receive "
								"return code: " + to_string( r ) );
				}
			},
			4,
			"simple test for msg_bag" );
	}
	catch( const exception & ex )
	{
		cerr << "Error: " << ex.what() << endl;
		return 1;
	}

	return 0;
}

