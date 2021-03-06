# Set the data directory to the directory created by the ExternalData.cmake
# script

set(RTK_DATA_ROOT ${CMAKE_BINARY_DIR}/ExternalData/testing/Data CACHE PATH "Path of the data root")
MARK_AS_ADVANCED(RTK_DATA_ROOT)

CONFIGURE_FILE (${CMAKE_CURRENT_SOURCE_DIR}/rtkTestConfiguration.h.in
  ${CMAKE_BINARY_DIR}/rtkTestConfiguration.h)

# Macro to add CUDA test from regular test
macro(add_cuda_test testname testfile)
 if(RTK_USE_CUDA AND CUDA_HAVE_GPU)
   set(testfullname ${testname}cudatest)
   add_executable(${testfullname} ${testfile})
   target_link_libraries(${testfullname} ${RTK_LIBRARIES})
   set_target_properties(${testfullname} PROPERTIES COMPILE_FLAGS -DUSE_CUDA)
   add_test(${testfullname} ${EXECUTABLE_OUTPUT_PATH}/${testfullname})
 endif()
endmacro()

# Macro to add CUDA test when external data is required
macro(rtk_add_cuda_test testname testfile)
 if(RTK_USE_CUDA AND CUDA_HAVE_GPU)
   set(testfullname ${testname}cudatest)
   add_executable(${testfullname} ${testfile})
   target_link_libraries(${testfullname} ${RTK_LIBRARIES})
   set_target_properties(${testfullname} PROPERTIES COMPILE_FLAGS -DUSE_CUDA)
   set(data_list "")
   foreach(loop_data ${ARGN})
      set(data_list "${data_list} DATA{${loop_data}}")
   endforeach()
   RTK_ADD_TEST(NAME ${testfullname}
		COMMAND ${EXECUTABLE_OUTPUT_PATH}/${testfullname}
		${data_list}
		)
 endif()
endmacro()

# Executable to check the image quality
ADD_EXECUTABLE(rtkcheckimagequality rtkcheckimagequality.cxx)
TARGET_LINK_LIBRARIES(rtkcheckimagequality ${RTK_LIBRARIES})

ADD_EXECUTABLE(rtkfdktest rtkfdktest.cxx)
TARGET_LINK_LIBRARIES(rtkfdktest ${RTK_LIBRARIES})
ADD_TEST(rtkfdktest ${EXECUTABLE_OUTPUT_PATH}/rtkfdktest)
ADD_CUDA_TEST(rtkfdk rtkfdktest.cxx)
ADD_CUDA_TEST(rtkfdkprojweightcomp rtkfdkprojweightcompcudatest.cxx)

ADD_EXECUTABLE(rtkimporttest rtkimporttest.cxx)
TARGET_LINK_LIBRARIES(rtkimporttest ${RTK_LIBRARIES})
ADD_TEST(rtkimporttest ${EXECUTABLE_OUTPUT_PATH}/rtkimporttest)
ADD_CUDA_TEST(rtkimport rtkimporttest.cxx)

ADD_CUDA_TEST(rtkcropfilter rtkcroptest.cxx)

ADD_EXECUTABLE(rtkmotioncompensatedfdktest rtkmotioncompensatedfdktest.cxx)
TARGET_LINK_LIBRARIES(rtkmotioncompensatedfdktest ${RTK_LIBRARIES})
ADD_TEST(rtkmotioncompensatedfdktest ${EXECUTABLE_OUTPUT_PATH}/rtkmotioncompensatedfdktest)

ADD_EXECUTABLE(rtkdisplaceddetectortest rtkdisplaceddetectortest.cxx)
TARGET_LINK_LIBRARIES(rtkdisplaceddetectortest ${RTK_LIBRARIES})
ADD_TEST(rtkdisplaceddetectortest ${EXECUTABLE_OUTPUT_PATH}/rtkdisplaceddetectortest)
ADD_CUDA_TEST(rtkdisplaceddetectortest rtkdisplaceddetectortest.cxx)
ADD_CUDA_TEST(rtkdisplaceddetectorcomp rtkdisplaceddetectorcompcudatest.cxx)

ADD_EXECUTABLE(rtkdisplaceddetectorcompoffsettest rtkdisplaceddetectorcompoffsettest.cxx)
TARGET_LINK_LIBRARIES(rtkdisplaceddetectorcompoffsettest ${RTK_LIBRARIES})
ADD_TEST(rtkdisplaceddetectorcompoffsettest ${EXECUTABLE_OUTPUT_PATH}/rtkdisplaceddetectorcompoffsettest)

ADD_EXECUTABLE(rtkshortscantest rtkshortscantest.cxx)
TARGET_LINK_LIBRARIES(rtkshortscantest ${RTK_LIBRARIES})
ADD_TEST(rtkshortscantest ${EXECUTABLE_OUTPUT_PATH}/rtkshortscantest)
ADD_CUDA_TEST(rtkshortscantest rtkshortscantest.cxx)
ADD_CUDA_TEST(rtkshortscancomp rtkshortscancompcudatest.cxx)

ADD_EXECUTABLE(rtkrampfiltertest rtkrampfiltertest.cxx)
TARGET_LINK_LIBRARIES(rtkrampfiltertest ${RTK_LIBRARIES})
ADD_TEST(rtkrampfiltertest ${EXECUTABLE_OUTPUT_PATH}/rtkrampfiltertest)
ADD_CUDA_TEST(rtkrampfilter rtkrampfiltertest.cxx)

ADD_EXECUTABLE(rtkrampfiltertest2 rtkrampfiltertest2.cxx)
TARGET_LINK_LIBRARIES(rtkrampfiltertest2 ${RTK_LIBRARIES})
ADD_TEST(rtkrampfiltertest2 ${EXECUTABLE_OUTPUT_PATH}/rtkrampfiltertest2)
ADD_CUDA_TEST(rtkrampfilter2 rtkrampfiltertest2.cxx)

ADD_EXECUTABLE(rtkrampfilternofftwtest rtkrampfiltertest.cxx)
SET_TARGET_PROPERTIES(rtkrampfilternofftwtest PROPERTIES COMPILE_FLAGS -DRAMP_FILTER_TEST_WITHOUT_FFTW)
TARGET_LINK_LIBRARIES(rtkrampfilternofftwtest ${RTK_LIBRARIES})
ADD_TEST(rtkrampfilternofftwtest ${EXECUTABLE_OUTPUT_PATH}/rtkrampfilternofftwtest)
IF(RTK_USE_CUDA AND CUDA_HAVE_GPU)
  ADD_EXECUTABLE(rtkrampfilternofftwcudatest rtkrampfiltertest.cxx)
  TARGET_LINK_LIBRARIES(rtkrampfilternofftwcudatest ${RTK_LIBRARIES})
  SET_TARGET_PROPERTIES(rtkrampfilternofftwcudatest PROPERTIES COMPILE_FLAGS "-DUSE_CUDA -DRAMP_FILTER_TEST_WITHOUT_FFTW")
  ADD_TEST(rtkrampfilternofftwcudatest ${EXECUTABLE_OUTPUT_PATH}/rtkrampfilternofftwcudatest)
ENDIF(RTK_USE_CUDA AND CUDA_HAVE_GPU)

ADD_EXECUTABLE(rtkscatterglarefiltertest rtkscatterglarefiltertest.cxx)
TARGET_LINK_LIBRARIES(rtkscatterglarefiltertest ${RTK_LIBRARIES})
ADD_TEST(rtkscatterglarefiltertest ${EXECUTABLE_OUTPUT_PATH}/rtkscatterglarefiltertest)
ADD_CUDA_TEST(rtkscatterglarefilter rtkscatterglarefiltertest.cxx)

ADD_EXECUTABLE(rtkgaincorrectiontest rtkgaincorrectiontest.cxx)
TARGET_LINK_LIBRARIES(rtkgaincorrectiontest ${RTK_LIBRARIES})
ADD_TEST(rtkgaincorrectiontest ${EXECUTABLE_OUTPUT_PATH}/rtkgaincorrectiontest)
ADD_CUDA_TEST(rtkgaincorrectiontest rtkgaincorrectiontest.cxx)

ADD_EXECUTABLE(rtkscatterglarefilternofftwtest rtkscatterglarefiltertest.cxx)
SET_TARGET_PROPERTIES(rtkscatterglarefilternofftwtest PROPERTIES COMPILE_FLAGS -DRAMP_FILTER_TEST_WITHOUT_FFTW)
TARGET_LINK_LIBRARIES(rtkscatterglarefilternofftwtest ${RTK_LIBRARIES})

ADD_EXECUTABLE(rtkRaycastInterpolatorForwardProjectionTest rtkRaycastInterpolatorForwardProjectionTest.cxx)
TARGET_LINK_LIBRARIES(rtkRaycastInterpolatorForwardProjectionTest ${RTK_LIBRARIES})
ADD_TEST(rtkRaycastInterpolatorForwardProjectionTest ${EXECUTABLE_OUTPUT_PATH}/rtkRaycastInterpolatorForwardProjectionTest)

ADD_EXECUTABLE(rtkforwardprojectiontest rtkforwardprojectiontest.cxx)
TARGET_LINK_LIBRARIES(rtkforwardprojectiontest ${RTK_LIBRARIES})
ADD_TEST(rtkforwardprojectiontest ${EXECUTABLE_OUTPUT_PATH}/rtkforwardprojectiontest)
ADD_CUDA_TEST(rtkforwardprojection rtkforwardprojectiontest.cxx)

ADD_EXECUTABLE(rtkgeometryfiletest rtkgeometryfiletest.cxx)
TARGET_LINK_LIBRARIES(rtkgeometryfiletest ${RTK_LIBRARIES})
ADD_TEST(rtkgeometryfiletest ${EXECUTABLE_OUTPUT_PATH}/rtkgeometryfiletest)

ADD_EXECUTABLE(rtkTestReg23ProjectionGeometry rtkTestReg23ProjectionGeometry.cxx)
TARGET_LINK_LIBRARIES(rtkTestReg23ProjectionGeometry ${RTK_LIBRARIES})
ADD_TEST(rtkTestReg23ProjectionGeometry ${EXECUTABLE_OUTPUT_PATH}/rtkTestReg23ProjectionGeometry)

ADD_EXECUTABLE(rtkfovtest rtkfovtest.cxx)
TARGET_LINK_LIBRARIES(rtkfovtest ${RTK_LIBRARIES})
ADD_TEST(rtkfovtest ${EXECUTABLE_OUTPUT_PATH}/rtkfovtest)

ADD_EXECUTABLE(rtkbinningtest rtkbinningtest.cxx)
TARGET_LINK_LIBRARIES(rtkbinningtest ${RTK_LIBRARIES})
ADD_TEST(rtkbinningtest ${EXECUTABLE_OUTPUT_PATH}/rtkbinningtest)

ADD_EXECUTABLE(rtkl0gradientnormtest rtkl0gradientnormtest.cxx)
TARGET_LINK_LIBRARIES(rtkl0gradientnormtest ${RTK_LIBRARIES})
ADD_TEST(rtkl0gradientnormtest ${EXECUTABLE_OUTPUT_PATH}/rtkl0gradientnormtest)

ADD_EXECUTABLE(rtkmediantest rtkmediantest.cxx)
TARGET_LINK_LIBRARIES(rtkmediantest ${RTK_LIBRARIES})
ADD_TEST(rtkmediantest ${EXECUTABLE_OUTPUT_PATH}/rtkmediantest)

ADD_EXECUTABLE(rtkwaterprecorrectiontest rtkwaterprecorrectiontest.cxx)
TARGET_LINK_LIBRARIES(rtkwaterprecorrectiontest ${RTK_LIBRARIES})
ADD_TEST(rtkwaterprecorrectiontest ${EXECUTABLE_OUTPUT_PATH}/rtkwaterprecorrectiontest)

ADD_EXECUTABLE(rtklutbasedvarI0rawtoatttest rtklutbasedvarI0rawtoatttest.cxx)
TARGET_LINK_LIBRARIES(rtklutbasedvarI0rawtoatttest ${RTK_LIBRARIES})
ADD_TEST(rtklutbasedvarI0rawtoatttest ${EXECUTABLE_OUTPUT_PATH}/rtklutbasedvarI0rawtoatttest)

ADD_EXECUTABLE(rtkamsterdamshroudtest rtkamsterdamshroudtest.cxx)
TARGET_LINK_LIBRARIES(rtkamsterdamshroudtest ${RTK_LIBRARIES})
RTK_ADD_TEST(NAME rtkamsterdamshroudtest
             COMMAND ${EXECUTABLE_OUTPUT_PATH}/rtkamsterdamshroudtest
             DATA{Data/Baseline/AmsterdamShroud/Amsterdam_crop.mha}
             DATA{Data/Baseline/AmsterdamShroud/Amsterdam.mha})

ADD_EXECUTABLE(rtkvariantest rtkvariantest.cxx)
TARGET_LINK_LIBRARIES(rtkvariantest ${RTK_LIBRARIES})
RTK_ADD_TEST(NAME rtkvariantest
             COMMAND ${EXECUTABLE_OUTPUT_PATH}/rtkvariantest
             DATA{Data/Input/Varian/raw.hnd,acqui.xml}
             DATA{Data/Baseline/Varian/attenuation.mha,geometry.xml})

ADD_EXECUTABLE(rtkelektatest rtkelektatest.cxx)
TARGET_LINK_LIBRARIES(rtkelektatest ${RTK_LIBRARIES})
RTK_ADD_TEST(NAME rtkelektatest
             COMMAND ${EXECUTABLE_OUTPUT_PATH}/rtkelektatest
             DATA{Data/Input/Elekta/FRAME.DBF,IMAGE.DBF,raw.his,_Frames.xml}
             DATA{Data/Baseline/Elekta/geometry.xml,attenuation.mha,geometry5.xml})

ADD_EXECUTABLE(rtkluttest rtkluttest.cxx)
TARGET_LINK_LIBRARIES(rtkluttest ${RTK_LIBRARIES})
RTK_ADD_TEST(NAME rtkluttest
             COMMAND ${EXECUTABLE_OUTPUT_PATH}/rtkluttest
             DATA{Data/Input/Elekta/raw.his}
             DATA{Data/Baseline/Elekta/attenuation.mha})

ADD_EXECUTABLE(rtkimagxtest rtkimagxtest.cxx)
TARGET_LINK_LIBRARIES(rtkimagxtest ${RTK_LIBRARIES})
RTK_ADD_TEST(NAME rtkimagxtest
             COMMAND ${EXECUTABLE_OUTPUT_PATH}/rtkimagxtest
             DATA{Data/Input/ImagX/calibration.xml,room.xml,raw.xml,raw.raw,1.dcm}
             DATA{Data/Baseline/ImagX/geo.xml,attenuation.mha,attenuationDCM.mha})

ADD_EXECUTABLE(rtkedftest rtkedftest.cxx)
TARGET_LINK_LIBRARIES(rtkedftest ${RTK_LIBRARIES})
RTK_ADD_TEST(NAME rtkedftest
             COMMAND ${EXECUTABLE_OUTPUT_PATH}/rtkedftest
             DATA{Data/Input/ESRF/raw.edf,dark.edf,refHST0000.edf}
             DATA{Data/Baseline/ESRF/attenuation.mha})

ADD_EXECUTABLE(rtkdigisenstest rtkdigisenstest.cxx)
TARGET_LINK_LIBRARIES(rtkdigisenstest ${RTK_LIBRARIES})
RTK_ADD_TEST(NAME rtkdigisenstest
             COMMAND ${EXECUTABLE_OUTPUT_PATH}/rtkdigisenstest
             DATA{Data/Input/Digisens/ima0010.tif,calibration.cal},
             DATA{Data/Baseline/Digisens/attenuation.mha,geometry.xml})

ADD_EXECUTABLE(rtkxradtest rtkxradtest.cxx)
TARGET_LINK_LIBRARIES(rtkxradtest ${RTK_LIBRARIES})
RTK_ADD_TEST(NAME rtkxradtest
             WORKING_DIRECTORY ${RTK_DATA_ROOT}/Input/XRad
             COMMAND ${EXECUTABLE_OUTPUT_PATH}/rtkxradtest
             DATA{Data/Input/XRad/flat.header,flat.img,dark.header,dark.img,SolidWater_HiGain1x1.header,SolidWater_HiGain1x1_firstProj.header,SolidWater_HiGain1x1_firstProj.img}
             DATA{Data/Baseline/XRad/geometry.xml,attenuation.mha})

ADD_EXECUTABLE(rtkprojectgeometricphantomtest rtkprojectgeometricphantomtest.cxx)
TARGET_LINK_LIBRARIES(rtkprojectgeometricphantomtest ${RTK_LIBRARIES})
RTK_ADD_TEST(NAME rtkprojectgeometricphantomtest
             COMMAND ${EXECUTABLE_OUTPUT_PATH}/rtkprojectgeometricphantomtest
             DATA{Data/Input/GeometricPhantom/SheppLogan.txt})

ADD_EXECUTABLE(rtkdrawgeometricphantomtest rtkdrawgeometricphantomtest.cxx)
TARGET_LINK_LIBRARIES(rtkdrawgeometricphantomtest ${RTK_LIBRARIES})
RTK_ADD_TEST(NAME rtkdrawgeometricphantomtest
             COMMAND ${EXECUTABLE_OUTPUT_PATH}/rtkdrawgeometricphantomtest
             DATA{Data/Input/GeometricPhantom/SheppLogan.txt}
             DATA{Data/Input/GeometricPhantom/Geometries.txt})

ADD_EXECUTABLE(rtksarttest rtksarttest.cxx)
TARGET_LINK_LIBRARIES(rtksarttest ${RTK_LIBRARIES})
ADD_TEST(rtksarttest ${EXECUTABLE_OUTPUT_PATH}/rtksarttest)
ADD_CUDA_TEST(rtksart rtksarttest.cxx)

ADD_EXECUTABLE(rtkfourdsarttest rtkfourdsarttest.cxx)
TARGET_LINK_LIBRARIES(rtkfourdsarttest ${RTK_LIBRARIES})
ADD_TEST(rtkfourdsarttest ${EXECUTABLE_OUTPUT_PATH}/rtkfourdsarttest)
ADD_CUDA_TEST(rtkfourdsart rtkfourdsarttest.cxx)

ADD_EXECUTABLE(rtkfourdconjugategradienttest rtkfourdconjugategradienttest.cxx)
TARGET_LINK_LIBRARIES(rtkfourdconjugategradienttest ${RTK_LIBRARIES})
ADD_TEST(rtkfourdconjugategradienttest ${EXECUTABLE_OUTPUT_PATH}/rtkfourdconjugategradienttest)
ADD_CUDA_TEST(rtkfourdconjugategradient rtkfourdconjugategradienttest.cxx)

ADD_EXECUTABLE(rtkwarpfourdtoprojectionstacktest rtkwarpfourdtoprojectionstacktest.cxx)
TARGET_LINK_LIBRARIES(rtkwarpfourdtoprojectionstacktest ${RTK_LIBRARIES})
ADD_TEST(rtkwarpfourdtoprojectionstacktest ${EXECUTABLE_OUTPUT_PATH}/rtkwarpfourdtoprojectionstacktest)
ADD_CUDA_TEST(rtkwarpfourdtoprojectionstack rtkwarpfourdtoprojectionstacktest.cxx)

ADD_EXECUTABLE(rtkwarpprojectionstacktofourdtest rtkwarpprojectionstacktofourdtest.cxx)
TARGET_LINK_LIBRARIES(rtkwarpprojectionstacktofourdtest ${RTK_LIBRARIES})
ADD_TEST(rtkwarpprojectionstacktofourdtest ${EXECUTABLE_OUTPUT_PATH}/rtkwarpprojectionstacktofourdtest)
ADD_CUDA_TEST(rtkwarpprojectionstacktofourd rtkwarpprojectionstacktofourdtest.cxx)

ADD_EXECUTABLE(rtkjosephadjointoperatorstest rtkjosephadjointoperatorstest.cxx)
TARGET_LINK_LIBRARIES(rtkjosephadjointoperatorstest ${RTK_LIBRARIES})
ADD_TEST(rtkjosephadjointoperatorstest ${EXECUTABLE_OUTPUT_PATH}/rtkjosephadjointoperatorstest)

ADD_EXECUTABLE(rtkfourdadjointoperatorstest rtkfourdadjointoperatorstest.cxx)
TARGET_LINK_LIBRARIES(rtkfourdadjointoperatorstest ${RTK_LIBRARIES})
RTK_ADD_TEST(NAME rtkfourdadjointoperatorstest
             COMMAND ${EXECUTABLE_OUTPUT_PATH}/rtkfourdadjointoperatorstest
             DATA{Data/Input/Phases/phases_slow.txt})

ADD_EXECUTABLE(rtkinterpolatesplatadjointtest rtkinterpolatesplatadjointtest.cxx)
TARGET_LINK_LIBRARIES(rtkinterpolatesplatadjointtest ${RTK_LIBRARIES})
RTK_ADD_TEST(NAME rtkinterpolatesplatadjointtest
             COMMAND ${EXECUTABLE_OUTPUT_PATH}/rtkinterpolatesplatadjointtest
             DATA{Data/Input/Phases/phases_slow.txt})

ADD_EXECUTABLE(rtklaplaciantest rtklaplaciantest.cxx)
TARGET_LINK_LIBRARIES(rtklaplaciantest ${RTK_LIBRARIES})
RTK_ADD_TEST(NAME rtklaplaciantest 
	     COMMAND ${EXECUTABLE_OUTPUT_PATH}/rtklaplaciantest
	     DATA{Data/Baseline/Laplacian/Laplacian.mha})
RTK_ADD_CUDA_TEST(rtklaplacian rtklaplaciantest.cxx "Data/Baseline/Laplacian/Laplacian.mha")

ADD_EXECUTABLE(rtktotalvariationtest rtktotalvariationtest.cxx)
TARGET_LINK_LIBRARIES(rtktotalvariationtest ${RTK_LIBRARIES})
ADD_TEST(rtktotalvariationtest ${EXECUTABLE_OUTPUT_PATH}/rtktotalvariationtest)

ADD_EXECUTABLE(rtkgradienttest rtkgradienttest.cxx)
TARGET_LINK_LIBRARIES(rtkgradienttest ${RTK_LIBRARIES})
ADD_TEST(rtkgradienttest ${EXECUTABLE_OUTPUT_PATH}/rtkgradienttest)

ADD_EXECUTABLE(rtkdivergencetest rtkdivergencetest.cxx)
TARGET_LINK_LIBRARIES(rtkdivergencetest ${RTK_LIBRARIES})
ADD_TEST(rtkdivergencetest ${EXECUTABLE_OUTPUT_PATH}/rtkdivergencetest)

ADD_EXECUTABLE(rtklagcorrectiontest rtklagcorrectiontest.cxx)
TARGET_LINK_LIBRARIES(rtklagcorrectiontest ${RTK_LIBRARIES})
ADD_TEST(rtklagcorrectiontest ${EXECUTABLE_OUTPUT_PATH}/rtklagcorrectiontest)
ADD_CUDA_TEST(rtklagcorrection rtklagcorrectiontest.cxx)

ADD_EXECUTABLE(rtkconjugategradienttest rtkconjugategradienttest.cxx)
TARGET_LINK_LIBRARIES(rtkconjugategradienttest ${RTK_LIBRARIES})
ADD_TEST(rtkconjugategradienttest ${EXECUTABLE_OUTPUT_PATH}/rtkconjugategradienttest)

ADD_EXECUTABLE(rtkwarptest rtkwarptest.cxx)
TARGET_LINK_LIBRARIES(rtkwarptest ${RTK_LIBRARIES})
ADD_TEST(rtkwarptest ${EXECUTABLE_OUTPUT_PATH}/rtkwarptest)

ADD_EXECUTABLE(rtkI0estimationtest rtkI0estimationtest.cxx)
TARGET_LINK_LIBRARIES(rtkI0estimationtest ${RTK_LIBRARIES})
ADD_TEST(rtkI0estimationtest ${EXECUTABLE_OUTPUT_PATH}/rtkI0estimationtest)

IF(ITK_VERSION VERSION_GREATER 4.3.2)
  ADD_EXECUTABLE(rtkselectoneprojpercycletest rtkselectoneprojpercycletest.cxx)
  TARGET_LINK_LIBRARIES(rtkselectoneprojpercycletest ${RTK_LIBRARIES})
  ADD_TEST(rtkselectoneprojpercycletest ${EXECUTABLE_OUTPUT_PATH}/rtkselectoneprojpercycletest)
ENDIF()

# We cannot compile these tests using CPU if GPU is present
# This is because of rtkIterativeConeBeamReconstructionFilter
if(NOT RTK_USE_CUDA)
  ADD_EXECUTABLE(rtkiterativefdktest rtkiterativefdktest.cxx)
  TARGET_LINK_LIBRARIES(rtkiterativefdktest ${RTK_LIBRARIES})
  ADD_TEST(rtkiterativefdktest ${EXECUTABLE_OUTPUT_PATH}/rtkiterativefdktest)

  ADD_EXECUTABLE(rtkconjugategradientreconstructiontest rtkconjugategradientreconstructiontest.cxx)
  TARGET_LINK_LIBRARIES(rtkconjugategradientreconstructiontest ${RTK_LIBRARIES})
  ADD_TEST(rtkconjugategradientreconstructiontest ${EXECUTABLE_OUTPUT_PATH}/rtkconjugategradientreconstructiontest)

  ADD_EXECUTABLE(rtkfourdroostertest rtkfourdroostertest.cxx)
  TARGET_LINK_LIBRARIES(rtkfourdroostertest ${RTK_LIBRARIES})
  ADD_TEST(rtkfourdroostertest ${EXECUTABLE_OUTPUT_PATH}/rtkfourdroostertest)

  ADD_EXECUTABLE(rtkadmmwaveletstest rtkadmmwaveletstest.cxx)
  TARGET_LINK_LIBRARIES(rtkadmmwaveletstest RTK)
  ADD_TEST(rtkadmmwaveletstest ${EXECUTABLE_OUTPUT_PATH}/rtkadmmwaveletstest)

  ADD_EXECUTABLE(rtkadmmtotalvariationtest rtkadmmtotalvariationtest.cxx)
  TARGET_LINK_LIBRARIES(rtkadmmtotalvariationtest ${RTK_LIBRARIES})
  RTK_ADD_TEST(NAME rtkadmmtotalvariationtest
               COMMAND ${EXECUTABLE_OUTPUT_PATH}/rtkadmmtotalvariationtest
               DATA{Data/Input/Phases/phases.txt}
               DATA{Data/Input/Phases/phases_3projs.txt})

  ADD_EXECUTABLE(rtkregularizedconjugategradienttest rtkregularizedconjugategradienttest.cxx)
  TARGET_LINK_LIBRARIES(rtkregularizedconjugategradienttest RTK)
  ADD_TEST(rtkregularizedconjugategradienttest ${EXECUTABLE_OUTPUT_PATH}/rtkregularizedconjugategradienttest)
  
  ADD_EXECUTABLE(rtkcyclicdeformationtest rtkcyclicdeformationtest.cxx)
  TARGET_LINK_LIBRARIES(rtkcyclicdeformationtest RTK)
  ADD_TEST(rtkcyclicdeformationtest ${EXECUTABLE_OUTPUT_PATH}/rtkcyclicdeformationtest)
endif()
ADD_CUDA_TEST(rtkiterativefdk rtkiterativefdktest.cxx)
ADD_CUDA_TEST(rtkconjugategradientreconstruction rtkconjugategradientreconstructiontest.cxx)
ADD_CUDA_TEST(rtkfourdrooster rtkfourdroostertest.cxx)
ADD_CUDA_TEST(rtkadmmwavelets rtkadmmwaveletstest.cxx)
RTK_ADD_CUDA_TEST(rtkadmmtotalvariation rtkadmmtotalvariationtest.cxx "Data/Input/Phases/phases.txt" "Data/Input/Phases/phases_3projs.txt")
ADD_CUDA_TEST(rtkregularizedconjugategradient rtkregularizedconjugategradienttest.cxx)
ADD_CUDA_TEST(rtkcudaraycastadjointoperatorstest rtkcudaraycastadjointoperatorstest.cxx)
ADD_CUDA_TEST(rtkcyclicdeformation rtkcyclicdeformationtest.cxx)

ADD_EXECUTABLE(rtkwaveletstest rtkwaveletstest.cxx)
TARGET_LINK_LIBRARIES(rtkwaveletstest RTK)
ADD_TEST(rtkwaveletstest ${EXECUTABLE_OUTPUT_PATH}/rtkwaveletstest)

# Test headers
FILE(GLOB RTK_ALL_HEADERS RELATIVE ${PROJECT_SOURCE_DIR}/code "${PROJECT_SOURCE_DIR}/code/rtk*.h")
FILE(WRITE ${CMAKE_CURRENT_BINARY_DIR}/rtkheadertest.cxx "#ifdef USE_CUDA\n")
FILE(GLOB RTK_CUDA_HEADERS RELATIVE ${PROJECT_SOURCE_DIR}/code "${PROJECT_SOURCE_DIR}/code/rtkCuda*.h")
FOREACH(RTK_CUDA_HEADER ${RTK_CUDA_HEADERS})
  FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/rtkheadertest.cxx "# include \"${RTK_CUDA_HEADER}\"\n")
  LIST(REMOVE_ITEM RTK_ALL_HEADERS ${RTK_CUDA_HEADER})
ENDFOREACH()
FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/rtkheadertest.cxx "#endif //USE_CUDA\n")

FOREACH(RTK_ALL_HEADER ${RTK_ALL_HEADERS})
  FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/rtkheadertest.cxx "#include \"${RTK_ALL_HEADER}\"\n")
ENDFOREACH()
FILE(READ rtkheadertestfooter.cxx RTKHEADERTESTFOOTER)
FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/rtkheadertest.cxx "\n\n${RTKHEADERTESTFOOTER}")

ADD_EXECUTABLE(rtkheadertest ${CMAKE_CURRENT_BINARY_DIR}/rtkheadertest.cxx)
IF(RTK_USE_CUDA)
  SET_TARGET_PROPERTIES(rtkheadertest PROPERTIES COMPILE_FLAGS -DUSE_CUDA)
ENDIF()

TARGET_LINK_LIBRARIES(rtkheadertest ${RTK_LIBRARIES})
ADD_TEST(rtkheadertest ${EXECUTABLE_OUTPUT_PATH}/rtkheadertest)

# Test the manager used to automatically clean up the gengetopt args_info structures
ADD_EXECUTABLE(rtkargsinfomanagertest rtkargsinfomanagertest.cxx)
TARGET_LINK_LIBRARIES(rtkargsinfomanagertest RTK)
ADD_TEST(rtkargsinfomanagertest ${EXECUTABLE_OUTPUT_PATH}/rtkargsinfomanagertest)
