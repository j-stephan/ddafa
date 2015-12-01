/*
 * SinkStage.h
 *
 *  Created on: 12.11.2015
 *      Author: Jan Stephan
 *
 *      The SinkStage uses its ImageHandler policy to save images or volumes that are being passed from
 *      previous pipeline stages.
 */

#ifndef SINKSTAGE_H_
#define SINKSTAGE_H_

#ifdef DDAFA_DEBUG
#include <iostream>
#endif

#include <string>
#include <utility>

#include "../image/Image.h"
#include "../image/StdImage.h"

#include "InputSide.h"

namespace ddafa
{
	namespace pipeline
	{
		template <class ImageHandler>
		class SinkStage : public InputSide<ddafa::image::Image<float, ddafa::impl::StdImage<float>>>
						, public ImageHandler
		{
			public:
				using input_type = ddafa::image::Image<float, ddafa::impl::StdImage<float>>;

			public:
				SinkStage(std::string path)
				: InputSide<input_type>(), ImageHandler(), target_dir_{path}
				{
				}

				void run()
				{
					while(true)
					{
						input_type img = this->input_queue_.take();
						if(img.valid())
							ImageHandler::template saveImage<float>(std::move(img), "/home/ufxray/Schreibtisch/Feldkamp/out.tif");
						else
						{
#ifdef DDAFA_DEBUG
							std::cout << "SinkStage: Poisonous pill arrived, terminating pipeline." << std::endl;
#endif
							break; // poisonous pill
						}

					}
				}

			private:
				std::string target_dir_;
		};
	}
}


#endif /* SINKSTAGE_H_ */
