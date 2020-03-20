#include <mitsuba/render/integrator.h>
#include <mitsuba/render/records.h>

NAMESPACE_BEGIN(mitsuba)

/**
 * \brief Example of one an extremely simple type of integrator that is also
 * helpful for debugging: returns the distance from the camera to the closest
 * intersected object, or 0 if no intersection was found.
 */
template <typename Float, typename Spectrum>
class DepthIntegrator final : public SamplingIntegrator<Float, Spectrum> {
public:
    MTS_IMPORT_BASE(SamplingIntegrator)
    MTS_IMPORT_TYPES(Scene, Sampler)

    DepthIntegrator(const Properties &props) : Base(props) { }

    void sample(std::vector<std::pair<std::pair<Spectrum, Mask>, Float>> *samples, 
                const Scene *scene,
                Sampler * /* sampler */,
                const RayDifferential3f &ray,
                Float * /* aovs */,
                Mask active) const override {
        MTS_MASKED_FUNCTION(ProfilerPhase::SamplingIntegratorSample, active);

        SurfaceInteraction3f si = scene->ray_intersect(ray, active);

        samples->push_back({ { select(si.is_valid(), si.t, 0.f), si.is_valid() }, 0.0f });
    }

    MTS_DECLARE_CLASS()
};

MTS_IMPLEMENT_CLASS_VARIANT(DepthIntegrator, SamplingIntegrator)
MTS_EXPORT_PLUGIN(DepthIntegrator, "Depth integrator");
NAMESPACE_END(mitsuba)
